// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_ALPHA_ZERO_EVALUATION_EVALUATOR_HPP
#define ROSETTASTONE_TORCH_ALPHA_ZERO_EVALUATION_EVALUATOR_HPP

#include <Agents/MCTSAgent.hpp>
#include <AlphaZero/Evaluation/CompetitionResult.hpp>
#include <AlphaZero/Evaluation/RunOptions.hpp>
#include <Judges/Judger.hpp>
#include <NeuralNet/NeuralNetwork.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaTorch::AlphaZero::Evaluation
{
//!
//! \brief Evaluator class.
//!
//! This class is a helper for evaluating the game that provides BeforeRun(),
//! Run() and AfterRun().
//!
class Evaluator
{
 public:
    //! Default destructor.
    ~Evaluator() = default;

    //! Deleted copy constructor.
    Evaluator(const Evaluator&) = delete;

    //! Deleted move constructor.
    Evaluator(Evaluator&&) noexcept = delete;

    //! Deleted copy assignment operator.
    Evaluator& operator=(const Evaluator&) = delete;

    //! Deleted move assignment operator.
    Evaluator& operator=(Evaluator&&) noexcept = delete;

    //! The method that runs before method Run().
    //! \param bestNetPath The path of the best neural network.
    //! \param competitorNetPath The path of the competitor neural network.
    //! \param result The result of the competition.
    void BeforeRun(const std::string& bestNetPath,
                   const std::string& competitorNetPath,
                   CompetitionResult& result);

    //! The main method of the evaluator.
    //! \param options The options of the runner.
    //! \param callback The callback to run.
    template <typename Callback>
    void Run(const RunOptions& options, Callback&& callback)
    {
        Agents::MCTSConfig bestAgentConfig = options.agentConfig;
        bestAgentConfig.mcts.neuralNetPath = m_bestNetPath;

        Agents::MCTSConfig competitorAgentConfig = options.agentConfig;
        competitorAgentConfig.mcts.neuralNetPath = m_competitorNetPath;

        while (callback())
        {
            Judges::NullRecorder recorder;
            Judges::Judger<Agents::MCTSAgent<>> judger(recorder);
            Agents::MCTSAgent<> bestAgent(bestAgentConfig);
            Agents::MCTSAgent<> competitorAgent(competitorAgentConfig);

            bool isCompetitorFirst = Random::get<int>(0, 1) == 0;
            if (isCompetitorFirst)
            {
                judger.SetPlayer1Agent(&competitorAgent);
                judger.SetPlayer2Agent(&bestAgent);
            }
            else
            {
                judger.SetPlayer1Agent(&bestAgent);
                judger.SetPlayer2Agent(&competitorAgent);
            }
        }
    }

    //! The method that runs after method Run().
    void AfterRun();

 private:
    CompetitionResult* m_result = nullptr;
    std::string m_bestNetPath;
    std::string m_competitorNetPath;
};
}  // namespace RosettaTorch::AlphaZero::Evaluation

#endif  // ROSETTASTONE_TORCH_ALPHA_ZERO_EVALUATION_EVALUATOR_HPP