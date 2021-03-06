/*
 * The GINA Bot - a computer opponent for Valve's FPS game Half-Life
 * Copyright (c) 2011, Wei Mingzhi <whistler_wmz@users.sf.net>
 *
 * This file is part of The GINA Bot.
 *
 * The GINA Bot is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 *
 * The GINA Bot is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with The GINA Bot; if not, visit <http://www.gnu.org/licenses>.
 *
 * In addition, as a special exception, the author gives permission to
 * link the code of this program with the Half-Life Game Engine ("HL
 * Engine") and Modified Game Libraries ("MODs") developed by Valve,
 * L.L.C ("Valve").  You must obey the GNU General Public License in all
 * respects for all of the code used other than the HL Engine and MODs
 * from Valve.  If you modify this file, you may extend this exception
 * to your version of the file, but you are not obligated to do so.  If
 * you do not wish to do so, delete this exception statement from your
 * version.
 */

//
// bot_ainet.cpp
//

#include "main.h"

// Enter new AI node
// usage: AIEnter(new CAINode_xxxx(this));
void CBaseBot::AIEnter(CAINode *pNode)
{
   if (!pNode) {
      CGeneral::TerminateOnError("CBaseBot::AIEnter(): pNode is NULL!");
   }

   if (!pNode->m_pBot) {
      CGeneral::TerminateOnError("CBaseBot::AIEnter(): pNode->m_pBot is NULL!");
   }

   if (m_pAINode) {
      DebugMsg(DEBUG_BOTAI, "** AI Node Exiting: %s **", m_pAINode->GetDescription());

      m_pAINode->OnExit(); // execute the exit event
      delete m_pAINode; // free the memory allocated for this node
      m_pAINode = NULL; // null out the pointer
   }

   DebugMsg(DEBUG_BOTAI, "** AI Node Entering: %s **", pNode->GetDescription());

   pNode->OnEnter(); // execute the enter event
   m_pAINode = pNode; // remember this node
}

// Run the AI network (Finite State Machine)
void CBaseBot::AINet_Run()
{
   int iCount = 0;

   while (m_pAINode->Run()) {
      iCount++;
      if (iCount > MAX_NODESWITCHES) {
         DebugMsg(DEBUG_BOTAI, "CBaseBot::AINet_Run(): %s at %1.1f switched more than %d AI nodes\n",
            GetNetName(), g_pServer->GetTime(), MAX_NODESWITCHES);
      }
   }
}

