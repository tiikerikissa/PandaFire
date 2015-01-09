/*
Début du script le boss Malkorok
Autor : ProjectCoreDevs
*/

#include "Player.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"


enum eMalkorokPhase
{
	PHASE_1 = 1,
	PHASE_2 = 2
};

enum eMalkorokSpells
{
	SPELL_ACIENT_MIASMA          = 142861, // 1
	SPELL_ARCING_SMASH           = 142826, // 2
	SPELL_SEISMIC_SLAM           = 142851, // 3
	SPELL_DISPLACED_ENERGY       = 142913, // 4
	SPELL_EXPEL_MIASMA           = 143199, // 5
	SPELL_BREATH_OF_YSHAARJ      = 142842, // 6
};

enum eMalkorokEvents
{
	EVENT_MALKOROK_1_1 = 1,
	EVENT_MALKOROK_1_2 = 2,
	EVENT_MALKOROK_1_3 = 3,
	EVENT_MALKOROK_2_1 = 4,
	EVENT_MALKOROK_2_2 = 5,
	EVENT_MALKOROK_2_3 = 6,
};

enum eMalkorokTalk
{
	TALK_INTRO = 0,
	TALK_AGGRO = 1,
	TALK_DEATH = 2,
};

// Malkorok - 71454
class boss_malkorok : public CreatureScript
{
public:
	boss_malkorok() : CreatureScript("boss_malkorok") {}

	struct boss_malkorokAI : public BossAI
	{
		boss_malkorokAI(Creature* creature) : BossAI(creature, 0){ }

		void Reset()
		{
			_Reset();
		}


		void EnterCombat(Unit* attacker)
		{
			events.ScheduleEvent(EVENT_MALKOROK_1_1, 2500);  // 2.5 sec
			events.ScheduleEvent(EVENT_MALKOROK_1_2, 5000);  // 5 sec
			events.ScheduleEvent(EVENT_MALKOROK_1_3, 10000); // 10 sec
			events.ScheduleEvent(EVENT_MALKOROK_2_1, 15000); // 15 sec
			events.ScheduleEvent(EVENT_MALKOROK_2_2, 20000); // 20 sec
			events.ScheduleEvent(EVENT_MALKOROK_2_3, 25000); // 25 sec

			//Talk(TALK_AGGRO);
		}
		
		void JustDied(Unit* killer)
		{
		}
		
		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim())
				return;

			events.Update(diff);

			if (me->HasUnitState(UNIT_STATE_CASTING))
				return;

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_MALKOROK_1_1:
					DoCastVictim(SPELL_ACIENT_MIASMA);
					events.ScheduleEvent(EVENT_MALKOROK_1_1, 2500); // 2.5 sec
					break;
				case EVENT_MALKOROK_1_2:
					DoCastVictim(SPELL_ARCING_SMASH);
					events.ScheduleEvent(EVENT_MALKOROK_1_2, 5000); // 5 sec
					break;
				case EVENT_MALKOROK_1_3:
					DoCastVictim(SPELL_ARCING_SMASH);
					events.ScheduleEvent(EVENT_MALKOROK_1_3, 10000); // 10 sec
					break;
				case EVENT_MALKOROK_2_1:
					DoCastVictim(SPELL_SEISMIC_SLAM);
					events.ScheduleEvent(EVENT_MALKOROK_2_1, 15000); // 15 sec
					break;
				case EVENT_MALKOROK_2_2:
					DoCastVictim(SPELL_DISPLACED_ENERGY);
					events.ScheduleEvent(EVENT_MALKOROK_2_2, 20000); // 20 sec
					break;
				case EVENT_MALKOROK_2_3:
					DoCastVictim(SPELL_BREATH_OF_YSHAARJ);
					events.ScheduleEvent(EVENT_MALKOROK_2_3, 25000); // 25 sec
					break;
				default:
					break;
				}
			}

			DoMeleeAttackIfReady();
		}
	};

	CreatureAI* GetAI(Creature* creature) const
	{
		return new boss_malkorokAI(creature);
	}
};

void AddSC_boss_malkorok()
{
	new boss_malkorok();
}
