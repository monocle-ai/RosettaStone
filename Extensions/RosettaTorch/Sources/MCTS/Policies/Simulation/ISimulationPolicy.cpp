// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <MCTS/Policies/Simulation/ISimulationPolicy.hpp>

namespace RosettaTorch::MCTS
{
ChoiceGetter::ChoiceGetter(int choices) : m_choices(choices)
{
    // Do nothing
}

std::size_t ChoiceGetter::Size() const
{
    return static_cast<std::size_t>(m_choices);
}

int ChoiceGetter::Get(std::size_t idx) const
{
    return static_cast<int>(idx);
}
}  // namespace RosettaTorch::MCTS