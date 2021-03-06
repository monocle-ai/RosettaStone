// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Commons/Constants.hpp>
#include <Rosetta/Tasks/SimpleTasks/TempManaTask.hpp>

namespace RosettaStone::SimpleTasks
{
TempManaTask::TempManaTask(int amount) : m_amount(amount)
{
    // Do nothing
}

TaskStatus TempManaTask::Impl(Player* player)
{
    if (player->GetRemainingMana() + m_amount > MANA_UPPER_LIMIT)
    {
        player->SetTemporaryMana(
            player->GetTemporaryMana() +
            (MANA_UPPER_LIMIT - player->GetRemainingMana()));
    }
    else
    {
        player->SetTemporaryMana(player->GetTemporaryMana() + m_amount);
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> TempManaTask::CloneImpl()
{
    return std::make_unique<TempManaTask>(m_amount);
}
}  // namespace RosettaStone::SimpleTasks
