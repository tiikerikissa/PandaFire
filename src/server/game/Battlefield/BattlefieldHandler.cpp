/*
 * Copyright (C) 2008-2010 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Common.h"
#include "ObjectAccessor.h"
#include "ObjectMgr.h"
#include "WorldPacket.h"
#include "WorldSession.h"

#include "Battlefield.h"
#include "BattlefieldMgr.h"
#include "Opcodes.h"

//This send to player windows for invite player to join the war
//Param1:(m_Guid) the BattleId of Bf
//Param2:(ZoneId) the zone where the battle is (4197 for wg)
//Param3:(time) Time in second that the player have for accept
void WorldSession::SendBfInvitePlayerToWar(uint64 guid, uint32 zoneId, uint32 pTime)
{
    //Send packet
    ObjectGuid guidBytes = guid;
    WorldPacket data(SMSG_BATTLEFIELD_MGR_ENTRY_INVITE);

    uint8 bitOrder[8] = {6, 5, 2, 4, 3, 0, 7, 1};
    data.WriteBitInOrder(guidBytes, bitOrder);

    data.WriteByteSeq(guidBytes[0]);
    data.WriteByteSeq(guidBytes[7]);
    data << uint32(time(NULL) + pTime); // Invite lasts until
    data.WriteByteSeq(guidBytes[6]);
    data.WriteByteSeq(guidBytes[5]);
    data.WriteByteSeq(guidBytes[3]);
    data << uint32(zoneId);         // Zone Id
    data.WriteByteSeq(guidBytes[1]);
    data.WriteByteSeq(guidBytes[4]);   
    data.WriteByteSeq(guidBytes[2]);
    //Sending the packet to player
    SendPacket(&data);
}

//This send invitation to player to join the queue
//Param1:(guid) the guid of Bf
void WorldSession::SendBfInvitePlayerToQueue(uint64 guid)
{
    ObjectGuid guidBytes = guid;
    bool warmup = true;

    WorldPacket data(SMSG_BATTLEFIELD_MGR_QUEUE_INVITE);
    
    data.WriteBit(1); // !+9
    data.WriteBit(guidBytes[2]);
    data.WriteBit(0); // +48
    data.WriteBit(guidBytes[7]);
    data.WriteBit(guidBytes[6]);
    data.WriteBit(1); // !+8
    data.WriteBit(guidBytes[1]);
    data.WriteBit(1); // !+11
    data.WriteBit(guidBytes[4]);
    data.WriteBit(guidBytes[5]);
    data.WriteBit(!warmup); // warmup
    data.WriteBit(guidBytes[0]);
    data.WriteBit(0); // -(bit != 0) +7 dword
    data.WriteBit(1); // +!6, dword
    data.WriteBit(guidBytes[3]);

    data.FlushBits();

    data.WriteByteSeq(guidBytes[6]);

    //if(-(bit != 0) +7 dword)
    //    data << uint32(0);

    //if(!+11)
    //    data << uint32(0);

    data.WriteByteSeq(guidBytes[5]);

    //if(!+6)
    //    data << uint32(0);

    //if(!+9)
    //    data << uint32(0);

    data.WriteByteSeq(guidBytes[7]);
    data.WriteByteSeq(guidBytes[1]);

    if(warmup)
        data << uint8(1);

    data.WriteByteSeq(guidBytes[2]);

    //if(+!8)
    //  data << uint32(0);

    data.WriteByteSeq(guidBytes[3]);
    data.WriteByteSeq(guidBytes[4]);
    data.WriteByteSeq(guidBytes[0]);

    //Sending packet to player
    SendPacket(&data);
}

//This send packet for inform player that he join queue
//Param1:(guid) the guid of Bf
//Param2:(ZoneId) the zone where the battle is (4197 for wg)
//Param3:(CanQueue) if able to queue
//Param4:(Full) on log in is full
void WorldSession::SendBfQueueInviteResponse(uint64 guid,uint32 ZoneId, bool CanQueue, bool Full)
{
    bool hasSecondGuid = false;
    ObjectGuid bgGuid = guid;
    WorldPacket data(SMSG_BATTLEFIELD_MGR_QUEUE_REQUEST_RESPONSE);
    data.WriteBit(bgGuid[4]);
    data.WriteBit(bgGuid[2]);
    data.WriteBit(bgGuid[5]);
    data.WriteBit(bgGuid[6]);
    data.WriteBit(bgGuid[3]);
    data.WriteBit(!hasSecondGuid); // Has Second guid
    data.WriteBit(bgGuid[1]);
    data.WriteBit(bgGuid[0]);

    data.WriteBit(0); // guid2[0]
    data.WriteBit(0); // guid2[1]
    data.WriteBit(0); // guid2[6]
    data.WriteBit(0); // guid2[5]
    data.WriteBit(0); // guid2[2]
    data.WriteBit(0); // guid2[4]
    data.WriteBit(0); // guid2[7]
    data.WriteBit(0); // guid2[3]

    data.WriteBit((Full ? 0 : 1)); // //Logging In        //0 wg full                 //1 queue for upcoming (we may need to swap it)
    data.WriteBit(bgGuid[7]);
    data.FlushBits();

    //if(guid2[1])
    //if(guid2[7])
    //if(guid2[4])
    //if(guid2[3])
    //if(guid2[6])
    //if(guid2[0])
    //if(guid2[2])
    //if(guid2[5])

    data.WriteByteSeq(bgGuid[6]);
    data.WriteByteSeq(bgGuid[5]);
    data.WriteByteSeq(bgGuid[4]);
    data.WriteByteSeq(bgGuid[0]);
    data << uint32(ZoneId);
    data.WriteByteSeq(bgGuid[1]);
    data << uint8(1); // Warmup
    data.WriteByteSeq(bgGuid[2]);
    data.WriteByteSeq(bgGuid[3]);
    data << uint8((CanQueue ? 1 : 0));  //Accepted          //0 you cannot queue wg     //1 you are queued
    data.WriteByteSeq(bgGuid[7]);

    SendPacket(&data);
}

//This is call when player accept to join war
//Param1:(guid) the guid of Bf
void WorldSession::SendBfEntered(uint64 guid)
{
    uint8 isAFK = _player->isAFK() ? 1 : 0;
    ObjectGuid guidBytes = guid;
    
	WorldPacket data(SMSG_BATTLEFIELD_MGR_ENTERING, 11);
    data.WriteBit(guidBytes[5]);
    data.WriteBit(guidBytes[0]);
    data.WriteBit(0);               // unk
    data.WriteBit(isAFK);           // Clear AFK
    data.WriteBit(guidBytes[7]);
    data.WriteBit(guidBytes[4]);
    data.WriteBit(guidBytes[2]);
    data.WriteBit(0);               // unk
    data.WriteBit(guidBytes[1]);
    data.WriteBit(guidBytes[3]);
    data.WriteBit(guidBytes[6]);

    data.FlushBits();

    data.WriteByteSeq(guidBytes[2]);
    data.WriteByteSeq(guidBytes[5]);
    data.WriteByteSeq(guidBytes[0]);
    data.WriteByteSeq(guidBytes[6]);
    data.WriteByteSeq(guidBytes[7]);
    data.WriteByteSeq(guidBytes[3]);
    data.WriteByteSeq(guidBytes[4]);
    data.WriteByteSeq(guidBytes[1]);
    SendPacket(&data);
}

void WorldSession::SendBfLeaveMessage(uint64 guid, BFLeaveReason reason)
{
    ObjectGuid guidBytes = guid;
	
    WorldPacket data(SMSG_BATTLEFIELD_MGR_EJECTED, 11);
    data.WriteBit(guidBytes[5]);
    data.WriteBit(0);               // Relocated
    data.WriteBit(guidBytes[4]);
    data.WriteBit(guidBytes[0]);
    data.WriteBit(guidBytes[2]);
    data.WriteBit(guidBytes[7]);
    data.WriteBit(guidBytes[1]);
    data.WriteBit(guidBytes[6]);
    data.WriteBit(guidBytes[3]);

    data.WriteByteSeq(guidBytes[0]);
    data.WriteByteSeq(guidBytes[2]);
    data.WriteByteSeq(guidBytes[3]);
    data.WriteByteSeq(guidBytes[4]);
    data.WriteByteSeq(guidBytes[6]);
    data.WriteByteSeq(guidBytes[5]);
    data << uint8(2);               // BattleStatus
    data << uint8(reason);          // Reason
    data.WriteByteSeq(guidBytes[7]);
    data.WriteByteSeq(guidBytes[1]);
    SendPacket(&data);
}

//Send by client when he click on accept for queue
void WorldSession::HandleBfQueueInviteResponse(WorldPacket & recvData)
{
    uint8 accepted;
    ObjectGuid guid;

    guid[3] = recvData.ReadBit();
    guid[6] = recvData.ReadBit();
    guid[0] = recvData.ReadBit();
    guid[2] = recvData.ReadBit();
    accepted = recvData.ReadBit();
    guid[1] = recvData.ReadBit();
    guid[5] = recvData.ReadBit();
    guid[7] = recvData.ReadBit();
    guid[4] = recvData.ReadBit();

    recvData.ReadByteSeq(guid[4]);
    recvData.ReadByteSeq(guid[1]);
    recvData.ReadByteSeq(guid[2]);
    recvData.ReadByteSeq(guid[6]);
    recvData.ReadByteSeq(guid[0]);
    recvData.ReadByteSeq(guid[7]);
    recvData.ReadByteSeq(guid[5]);
    recvData.ReadByteSeq(guid[3]);

    Battlefield* bf = sBattlefieldMgr->GetBattlefieldByGUID(guid);
    if (!bf)
        return;

    if (accepted)
        bf->PlayerAcceptInviteToQueue(_player);
}

//Send by client on clicking in accept or refuse of invitation windows for join game
void WorldSession::HandleBfEntryInviteResponse(WorldPacket & recvData)
{
    uint8 accepted;
    ObjectGuid guid;

    guid[0] = recvData.ReadBit();
    guid[7] = recvData.ReadBit();
    accepted = recvData.ReadBit();
    guid[4] = recvData.ReadBit();
    guid[3] = recvData.ReadBit();
    guid[1] = recvData.ReadBit();
    guid[6] = recvData.ReadBit();
    guid[2] = recvData.ReadBit();
    guid[5] = recvData.ReadBit();

    recvData.ReadByteSeq(guid[1]);
    recvData.ReadByteSeq(guid[6]);
    recvData.ReadByteSeq(guid[2]);
    recvData.ReadByteSeq(guid[5]);
    recvData.ReadByteSeq(guid[3]);
    recvData.ReadByteSeq(guid[4]);
    recvData.ReadByteSeq(guid[7]);
    recvData.ReadByteSeq(guid[0]);

    Battlefield* bf = sBattlefieldMgr->GetBattlefieldByGUID(guid);
    if (!bf)
        return;

    if (accepted)
        bf->PlayerAcceptInviteToWar(_player);
    else
        if (_player->GetZoneId() == bf->GetZoneId())
            bf->KickPlayerFromBattlefield(_player->GetGUID());
}

void WorldSession::HandleBfQueueRequest(WorldPacket& recvData)
{
    ObjectGuid guid;

    uint8 bitOrder[8] = {3, 5, 7, 0, 6, 2, 1, 4};
    recvData.ReadBitInOrder(guid, bitOrder);

    uint8 byteOrder[8] = {1, 0, 3, 2, 4, 7, 5, 6};
    recvData.ReadBytesSeq(guid, byteOrder);

    sLog->outError(LOG_FILTER_GENERAL, "HandleBfQueueRequest: GUID:" UI64FMTD " ", (uint64)guid);

    if (Battlefield* bf = sBattlefieldMgr->GetBattlefieldByGUID(guid))
    {
        if (bf->IsWarTime())
            bf->InvitePlayerToWar(_player);
        else
        {
            uint32 timer = bf->GetTimer() / 1000;
            if (timer < 15 * MINUTE)
                bf->InvitePlayerToQueue(_player);
        }
    }
}


void WorldSession::HandleBfExitQueueRequest(WorldPacket & recvData)
{
    ObjectGuid guid;

	guid[3] = recvData.ReadBit();
	guid[2] = recvData.ReadBit();
	guid[4] = recvData.ReadBit();
	guid[1] = recvData.ReadBit();
	guid[7] = recvData.ReadBit();
	guid[0] = recvData.ReadBit();
	guid[5] = recvData.ReadBit();
	guid[6] = recvData.ReadBit();

	recvData.ReadByteSeq(guid[5]);
	recvData.ReadByteSeq(guid[6]);
	recvData.ReadByteSeq(guid[2]);
	recvData.ReadByteSeq(guid[3]);
	recvData.ReadByteSeq(guid[0]);
	recvData.ReadByteSeq(guid[4]);
	recvData.ReadByteSeq(guid[7]);
	recvData.ReadByteSeq(guid[1]);

    sLog->outError(LOG_FILTER_GENERAL, "HandleBfExitQueueRequest: GUID:" UI64FMTD " ", (uint64)guid);

    SendBfLeaveMessage(guid);

    if (Battlefield* bf = sBattlefieldMgr->GetBattlefieldByGUID(guid))
        bf->AskToLeaveQueue(_player);
}

void WorldSession::HandleBfExitRequest(WorldPacket& recvData)
{
	ObjectGuid guid;

	guid[3] = recvData.ReadBit();
	guid[2] = recvData.ReadBit();
	guid[4] = recvData.ReadBit();
	guid[1] = recvData.ReadBit();
	guid[7] = recvData.ReadBit();
	guid[0] = recvData.ReadBit();
	guid[5] = recvData.ReadBit();
	guid[6] = recvData.ReadBit();

	recvData.ReadByteSeq(guid[5]);
	recvData.ReadByteSeq(guid[6]);
	recvData.ReadByteSeq(guid[2]);
	recvData.ReadByteSeq(guid[3]);
	recvData.ReadByteSeq(guid[0]);
	recvData.ReadByteSeq(guid[4]);
	recvData.ReadByteSeq(guid[7]);
	recvData.ReadByteSeq(guid[1]);

	// not allow leave battleground in combat
	if (_player->isInCombat())
	if (Battleground* bg = _player->GetBattleground())
	if (bg->GetStatus() != STATUS_WAIT_LEAVE)
		return;

	_player->LeaveBattleground();
}

void WorldSession::HandleReportPvPAFK(WorldPacket & recvData)
{
    uint64 playerGuid;
    recvData >> playerGuid;
    Player* reportedPlayer = ObjectAccessor::FindPlayer(playerGuid);

    if (!reportedPlayer)
    {
        sLog->outDebug(LOG_FILTER_BATTLEGROUND, "WorldSession::HandleReportPvPAFK: player not found");
        return;
    }

    sLog->outDebug(LOG_FILTER_BATTLEGROUND, "WorldSession::HandleReportPvPAFK: %s reported %s", _player->GetName(), reportedPlayer->GetName());

    reportedPlayer->ReportedAfkBy(_player);
}

void WorldSession::HandleRequestRatedBgInfo(WorldPacket & recvData)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: CMSG_REQUEST_RATED_BG_INFO");

    uint8 unk;
    recvData >> unk;

    sLog->outDebug(LOG_FILTER_BATTLEGROUND, "WorldSession::HandleRequestRatedBgInfo: get unk = %u", unk);

    /// @Todo: perfome research in this case
    WorldPacket data(SMSG_RATED_BG_STATS, 72);
    for (int32 i = 0; i < 18; ++i)
        data << uint32(0);
    SendPacket(&data);
}

void WorldSession::HandleRequestPvpOptions(WorldPacket& recvData)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: CMSG_REQUEST_PVP_OPTIONS_ENABLED");

    /// @Todo: perfome research in this case
    WorldPacket data(SMSG_PVP_OPTIONS_ENABLED, 1);
    data.WriteBit(1);
    data.WriteBit(1);
    data.WriteBit(1);
    data.WriteBit(1);
    data.WriteBit(1);
    data.FlushBits();
    SendPacket(&data);
}

void WorldSession::HandleRequestPvpReward(WorldPacket& recvData)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: CMSG_REQUEST_PVP_REWARDS");

    _player->SendPvpRewards();
}

void WorldSession::HandleRequestRatedBgStats(WorldPacket& recvData)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: CMSG_REQUEST_RATED_BG_STATS");

    WorldPacket data(SMSG_BATTLEFIELD_RATED_INFO, 29);
    data << uint32(0);  //rating
    data << uint32(0);  //unk1
    data << uint32(0);  //unk2
    //data << _player->GetCurrencyWeekCap(CURRENCY_TYPE_CONQUEST_META_BG, true);
    data << uint32(0);  //unk3
    data << _player->GetCurrency(CURRENCY_TYPE_CONQUEST_POINTS, true);
    data << uint8(3);   //unk4
    data << uint32(0);  //unk5
    SendPacket(&data);
}


void WorldSession::HandleBattlefieldLeaveOpcode(WorldPacket& /*recvData*/)
{
	sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Recvd CMSG_BATTLEFIELD_LEAVE Message");

	// not allow leave battleground in combat
	if (_player->isInCombat())
	if (Battleground* bg = _player->GetBattleground())
	if (bg->GetStatus() != STATUS_WAIT_LEAVE)
		return;

	_player->LeaveBattleground();
}