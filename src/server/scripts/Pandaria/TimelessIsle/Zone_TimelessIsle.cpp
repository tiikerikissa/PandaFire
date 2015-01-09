/*
* Copyright (C) 2014 <ProjectCoreDevs>
* Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
* Copyright (C) 2005-2014 MaNGOS <http://getmangos.com/>
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 3 of the License, or (at your
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

#include "Player.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "Unit.h"

/*################### NPC Zesqua 72245 ######################*/

enum SpellZesqua
{
	SPELL_ZESQUA_WATER_BLOSSOM = 147439,
	SPELL_ZESQUA_FURIOUS_SPLASH = 147335,
	SPELL_ZESQUA_WATER_BOLT_VOLLEY = 147344,
};

enum EventZesqua
{
	EVENT_ZESQUA_1 = 1,
	EVENT_ZESQUA_2 = 2,
	EVENT_ZESQUA_3 = 3,
};

class npc_Zesqua : public CreatureScript
{
public:
	npc_Zesqua() : CreatureScript("npc_Zesqua") { }

	struct npc_ZesquaAI : public BossAI
	{
		npc_ZesquaAI(Creature* creature) : BossAI(creature, 0)
		{
		}

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_ZESQUA_1, 5000); // 5 sec
			events.ScheduleEvent(EVENT_ZESQUA_2, 10000); // 10 sec
			events.ScheduleEvent(EVENT_ZESQUA_3, 20000); // 20 sec
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
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
				case EVENT_ZESQUA_1:
					DoCastVictim(SPELL_ZESQUA_WATER_BLOSSOM);
					events.ScheduleEvent(EVENT_ZESQUA_1, 5000); // 5 sec
					break;
				case EVENT_ZESQUA_2:
					DoCastVictim(SPELL_ZESQUA_FURIOUS_SPLASH);
					events.ScheduleEvent(EVENT_ZESQUA_2, 10000); // 10 sec
					break;
				case EVENT_ZESQUA_3:
					DoCastVictim(SPELL_ZESQUA_WATER_BOLT_VOLLEY);
					events.ScheduleEvent(EVENT_ZESQUA_3, 20000); // 20 sec
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
		return new npc_ZesquaAI(creature);
	}
};

/*################### NPC Spelurk 71864 ######################*/

enum SpellSpelurk
{
	SPELL_SPELURK_MURKY_CLOUD = 147805,
	SPELL_SPELURK_POISON_BREATH = 144892,
	SPELL_SPELURK_RENEWING_MISTS = 147769,
};

enum EventSpelurk
{
	EVENT_SPELURK_1 = 1,
	EVENT_SPELURK_2 = 2,
	EVENT_SPELURK_3 = 3,
};

class npc_Spelurk : public CreatureScript
{
public:
	npc_Spelurk() : CreatureScript("npc_Spelurk") { }

	struct npc_SpelurkAI : public BossAI
	{
		npc_SpelurkAI(Creature* creature) : BossAI(creature, 0)
		{
		}

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_SPELURK_1, 5000); // 5 sec
			events.ScheduleEvent(EVENT_SPELURK_2, 10000); // 10 sec
			events.ScheduleEvent(EVENT_SPELURK_3, 20000); // 20 sec
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
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
				case EVENT_SPELURK_1:
					DoCastVictim(SPELL_SPELURK_MURKY_CLOUD);
					events.ScheduleEvent(EVENT_SPELURK_1, 5000); // 5 sec
					break;
				case EVENT_SPELURK_2:
					DoCastVictim(SPELL_SPELURK_POISON_BREATH);
					events.ScheduleEvent(EVENT_SPELURK_2, 10000); // 10 sec
					break;
				case EVENT_SPELURK_3:
					DoCastVictim(SPELL_SPELURK_RENEWING_MISTS);
					events.ScheduleEvent(EVENT_SPELURK_3, 20000); // 20 sec
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
		return new npc_SpelurkAI(creature);
	}
};

/*################### NPC Karkanos <The Gushing Maw> 72193 ######################*/

enum SpellKarkanos
{
	SPELL_KARKANOS_GUSHING_MAW = 147843,
};

enum EventKarkanos
{
	EVENT_KARKANOS_1 = 1,
};

class npc_Karkanos : public CreatureScript
{
public:
	npc_Karkanos() : CreatureScript("npc_Karkanos") { }

	struct npc_KarkanosAI : public BossAI
	{
		npc_KarkanosAI(Creature* creature) : BossAI(creature, 0)
		{
		}

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_KARKANOS_1, 10000); // 5 sec
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
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
				case EVENT_KARKANOS_1:
					DoCastVictim(SPELL_KARKANOS_GUSHING_MAW);
					events.ScheduleEvent(EVENT_KARKANOS_1, 10000); // 10 sec
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
		return new npc_KarkanosAI(creature);
	}
};

/*################### NPC Emerald Gander 73158 ######################*/

enum SpellEmeraldGander
{
	SPELL_EMERALD_GANDER_WINDFEATHER = 147306,
	SPELL_EMERALD_GANDER_GUST_OF_WIND = 147310,
	SPELL_EMERALD_GANDER_HEALING_SONG = 147309,
};

enum EventEmeraldGander
{
	EVENT_EMERALD_GANDER_1 = 1,
	EVENT_EMERALD_GANDER_2 = 2,
	EVENT_EMERALD_GANDER_3 = 3,
};

class npc_EmeraldGander : public CreatureScript
{
public:
	npc_EmeraldGander() : CreatureScript("npc_EmeraldGander") { }

	struct npc_EmeraldGanderAI : public BossAI
	{
		npc_EmeraldGanderAI(Creature* creature) : BossAI(creature, 0)
		{
		}

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_EMERALD_GANDER_1, 5000); // 5 sec
			events.ScheduleEvent(EVENT_EMERALD_GANDER_2, 10000); // 10 sec
			events.ScheduleEvent(EVENT_EMERALD_GANDER_3, 20000); // 20 sec
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
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
				case EVENT_EMERALD_GANDER_1:
					DoCastVictim(SPELL_EMERALD_GANDER_WINDFEATHER);
					events.ScheduleEvent(EVENT_EMERALD_GANDER_1, 5000); // 5 sec
					break;
				case EVENT_EMERALD_GANDER_2:
					DoCastVictim(SPELL_EMERALD_GANDER_GUST_OF_WIND);
					events.ScheduleEvent(EVENT_EMERALD_GANDER_2, 10000); // 10 sec
					break;
				case EVENT_EMERALD_GANDER_3:
					DoCastVictim(SPELL_EMERALD_GANDER_HEALING_SONG);
					events.ScheduleEvent(EVENT_EMERALD_GANDER_3, 20000); // 20 sec
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
		return new npc_EmeraldGanderAI(creature);
	}
};

/*################### NPC Great Turtle Furyshell 73161 ######################*/

enum SpellGreatTurtleFuryshell
{
	SPELL_GREAT_TURTLE_FURYSHELL_SNAPPING_BITE = 147569,
	SPELL_GREAT_TURTLE_FURYSHELL_GEYSER = 147572,
	SPELL_GREAT_TURTLE_FURYSHELL_SHELL_SPIN = 147571,
};

enum EventGreatTurtleFuryshell
{
	EVENT_GREAT_TURTLE_FURYSHELL_1 = 1,
	EVENT_GREAT_TURTLE_FURYSHELL_2 = 2,
	EVENT_GREAT_TURTLE_FURYSHELL_3 = 3,
};

class npc_GreatTurtleFuryshell : public CreatureScript
{
public:
	npc_GreatTurtleFuryshell() : CreatureScript("npc_GreatTurtleFuryshell") { }

	struct npc_GreatTurtleFuryshellAI : public BossAI
	{
		npc_GreatTurtleFuryshellAI(Creature* creature) : BossAI(creature, 0)
		{
		}

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_GREAT_TURTLE_FURYSHELL_1, 5000); // 5 sec
			events.ScheduleEvent(EVENT_GREAT_TURTLE_FURYSHELL_2, 10000); // 10 sec
			events.ScheduleEvent(EVENT_GREAT_TURTLE_FURYSHELL_3, 20000); // 20 sec
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
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
				case EVENT_GREAT_TURTLE_FURYSHELL_1:
					DoCastVictim(SPELL_GREAT_TURTLE_FURYSHELL_SNAPPING_BITE);
					events.ScheduleEvent(EVENT_GREAT_TURTLE_FURYSHELL_1, 5000); // 5 sec
					break;
				case EVENT_GREAT_TURTLE_FURYSHELL_2:
					DoCastVictim(SPELL_GREAT_TURTLE_FURYSHELL_GEYSER);
					events.ScheduleEvent(EVENT_GREAT_TURTLE_FURYSHELL_2, 10000); // 10 sec
					break;
				case EVENT_GREAT_TURTLE_FURYSHELL_3:
					DoCastVictim(SPELL_GREAT_TURTLE_FURYSHELL_SHELL_SPIN);
					events.ScheduleEvent(EVENT_GREAT_TURTLE_FURYSHELL_3, 20000); // 20 sec
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
		return new npc_GreatTurtleFuryshellAI(creature);
	}
};

/*################### NPC Spirit of Jadefire 72769 ######################*/

enum SpellSpiritOfJadefire
{
	SPELL_SPIRIT_OF_JADEFIRE_JADEFIRE_BOLT = 147454,
	SPELL_SPIRIT_OF_JADEFIRE_JADELAME_STRIKE = 147456,
};

enum EventSpiritOfJadefire
{
	EVENT_SPIRIT_OF_JADEFIRE_1 = 1,
	EVENT_SPIRIT_OF_JADEFIRE_2 = 2,
};

class npc_SpiritOfJadefire : public CreatureScript
{
public:
	npc_SpiritOfJadefire() : CreatureScript("npc_SpiritOfJadefire") { }

	struct npc_SpiritOfJadefireAI : public BossAI
	{
		npc_SpiritOfJadefireAI(Creature* creature) : BossAI(creature, 0)
		{
		}

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_SPIRIT_OF_JADEFIRE_1, 10000); // 10 sec
			events.ScheduleEvent(EVENT_SPIRIT_OF_JADEFIRE_2, 20000); // 20 sec
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
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
				case EVENT_SPIRIT_OF_JADEFIRE_1:
					DoCastVictim(SPELL_SPIRIT_OF_JADEFIRE_JADEFIRE_BOLT);
					events.ScheduleEvent(EVENT_SPIRIT_OF_JADEFIRE_1, 10000); // 10 sec
					break;
				case EVENT_SPIRIT_OF_JADEFIRE_2:
					DoCastVictim(SPELL_SPIRIT_OF_JADEFIRE_JADELAME_STRIKE);
					events.ScheduleEvent(EVENT_SPIRIT_OF_JADEFIRE_2, 20000); // 20 sec
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
		return new npc_SpiritOfJadefireAI(creature);
	}
};

/*################### NPC Ironfur Steelhorn 73160 ######################*/

enum SpellIronfurSteelhorn
{
	SPELL_IRONFUR_STEELHORN_OX_CHARGE = 147386,
	SPELL_IRONFUR_STEELHORN_IRON_FUR = 147368,
	SPELL_IRONFUR_STEELHORN_HEADBUTT = 147384,
};

enum EventIronfurSteelhorn
{
	EVENT_IRONFUR_STEELHORN_1 = 1,
	EVENT_IRONFUR_STEELHORN_2 = 2,
	EVENT_IRONFUR_STEELHORN_3 = 3,
};

class npc_IronfurSteelhorn : public CreatureScript
{
public:
	npc_IronfurSteelhorn() : CreatureScript("npc_IronfurSteelhorn") { }

	struct npc_IronfurSteelhornAI : public BossAI
	{
		npc_IronfurSteelhornAI(Creature* creature) : BossAI(creature, 0)
		{
		}

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_IRONFUR_STEELHORN_1, 5000); // 5 sec
			events.ScheduleEvent(EVENT_IRONFUR_STEELHORN_2, 10000); // 10 sec
			events.ScheduleEvent(EVENT_IRONFUR_STEELHORN_3, 20000); // 20 sec
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
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
				case EVENT_IRONFUR_STEELHORN_1:
					DoCastVictim(SPELL_IRONFUR_STEELHORN_IRON_FUR);
					events.ScheduleEvent(EVENT_IRONFUR_STEELHORN_1, 5000); // 5 sec
					break;
				case EVENT_IRONFUR_STEELHORN_2:
					DoCastVictim(SPELL_IRONFUR_STEELHORN_OX_CHARGE);
					events.ScheduleEvent(EVENT_IRONFUR_STEELHORN_2, 10000); // 10 sec
					break;
				case EVENT_IRONFUR_STEELHORN_3:
					DoCastVictim(SPELL_IRONFUR_STEELHORN_HEADBUTT);
					events.ScheduleEvent(EVENT_IRONFUR_STEELHORN_3, 20000); // 20 sec
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
		return new npc_IronfurSteelhornAI(creature);
	}
};

/*################### NPC Chelon 72045 ######################*/

enum SpellChelon
{
	SPELL_CHELON_SNAPPING_BITE = 147569,
	SPELL_CHELON_GEYSER = 147572,
	SPELL_CHELON_SHELL_SPIN = 147571,
};

enum EventChelon
{
	EVENT_CHELON_1 = 1,
	EVENT_CHELON_2 = 2,
	EVENT_CHELON_3 = 3,
};

class npc_Chelon : public CreatureScript
{
public:
	npc_Chelon() : CreatureScript("npc_Chelon") { }

	struct npc_ChelonAI : public BossAI
	{
		npc_ChelonAI(Creature* creature) : BossAI(creature, 0)
		{
		}

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_CHELON_1, 5000); // 5 sec
			events.ScheduleEvent(EVENT_CHELON_2, 10000); // 10 sec
			events.ScheduleEvent(EVENT_CHELON_3, 20000); // 20 sec
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
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
				case EVENT_CHELON_1:
					DoCastVictim(SPELL_CHELON_SNAPPING_BITE);
					events.ScheduleEvent(EVENT_CHELON_1, 5000); // 5 sec
					break;
				case EVENT_CHELON_2:
					DoCastVictim(SPELL_CHELON_GEYSER);
					events.ScheduleEvent(EVENT_CHELON_2, 10000); // 10 sec
					break;
				case EVENT_CHELON_3:
					DoCastVictim(SPELL_CHELON_SHELL_SPIN);
					events.ScheduleEvent(EVENT_CHELON_3, 20000); // 20 sec
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
		return new npc_ChelonAI(creature);
	}
};

/*################### NPC Tsavoka <Ghost in the Darkness> 73163 ######################*/

enum SpellTsavoka
{
	SPELL_TSAVOKA_POUNCE = 147649,
	SPELL_TSAVOKA_GREATER_SWIPE = 147653,
};

enum EventTsavoka
{
	EVENT_TSAVOKA_1 = 1,
	EVENT_TSAVOKA_2 = 2,
};

class npc_Tsavoka : public CreatureScript
{
public:
	npc_Tsavoka() : CreatureScript("npc_Tsavoka") { }

	struct npc_TsavokaAI : public BossAI
	{
		npc_TsavokaAI(Creature* creature) : BossAI(creature, 0)
		{
		}

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_TSAVOKA_1, 5000); // 5 sec
			events.ScheduleEvent(EVENT_TSAVOKA_2, 15000); // 15 sec
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
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
				case EVENT_TSAVOKA_1:
					DoCastVictim(SPELL_TSAVOKA_POUNCE);
					events.ScheduleEvent(EVENT_TSAVOKA_1, 5000); // 5 sec
					break;
				case EVENT_TSAVOKA_2:
					DoCastVictim(SPELL_TSAVOKA_GREATER_SWIPE);
					events.ScheduleEvent(EVENT_TSAVOKA_2, 15000); // 15 sec
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
		return new npc_TsavokaAI(creature);
	}
};

/*################### NPC Imperial Python 73163 ######################*/

enum SpellImperialPython
{
	SPELL_IMPERIAL_PYTHON_HUGE_FANG = 147290,
};

enum EventImperialPython
{
	EVENT_IMPERIAL_PYTHON_1 = 1,
};

class npc_ImperialPython : public CreatureScript
{
public:
	npc_ImperialPython() : CreatureScript("npc_ImperialPython") { }

	struct npc_ImperialPythonAI : public BossAI
	{
		npc_ImperialPythonAI(Creature* creature) : BossAI(creature, 0)
		{
		}

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_IMPERIAL_PYTHON_1, 10000); // 10 sec
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
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
				case EVENT_IMPERIAL_PYTHON_1:
					DoCastVictim(SPELL_IMPERIAL_PYTHON_HUGE_FANG);
					events.ScheduleEvent(EVENT_IMPERIAL_PYTHON_1, 10000); // 10 sec
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
		return new npc_ImperialPythonAI(creature);
	}
};

/*################### NPC Monstrous Spineclaw 73166 ######################*/

enum SpellMonstrousSpineclaw
{
	SPELL_MONSTROUS_SPINECLAW_CLAW_FLURRY = 147560,
};

enum EventMonstrousSpineclaw
{
	EVENT_MONSTROUS_SPINECLAW_1 = 1,
};

class npc_MonstrousSpineclaw : public CreatureScript
{
public:
	npc_MonstrousSpineclaw() : CreatureScript("npc_MonstrousSpineclaw") { }

	struct npc_MonstrousSpineclawAI : public BossAI
	{
		npc_MonstrousSpineclawAI(Creature* creature) : BossAI(creature, 0)
		{
		}

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_MONSTROUS_SPINECLAW_1, 10000); // 10 sec
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
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
				case EVENT_MONSTROUS_SPINECLAW_1:
					DoCastVictim(SPELL_MONSTROUS_SPINECLAW_CLAW_FLURRY);
					events.ScheduleEvent(EVENT_MONSTROUS_SPINECLAW_1, 10000); // 10 sec
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
		return new npc_MonstrousSpineclawAI(creature);
	}
};

/*################### NPC Rock Moss 73157 ######################*/

enum SpellRockMoss
{
	SPELL_ROCK_MOSS_MURKY_CLOUD = 147805,
	SPELL_ROCK_MOSS_RENEWING_MISTS = 147769,
};

enum EventRockMoss
{
	EVENT_ROCK_MOSS_1 = 1,
	EVENT_ROCK_MOSS_2 = 2,
};

class npc_RockMoss : public CreatureScript
{
public:
	npc_RockMoss() : CreatureScript("npc_RockMoss") { }

	struct npc_RockMossAI : public BossAI
	{
		npc_RockMossAI(Creature* creature) : BossAI(creature, 0)
		{
		}

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_ROCK_MOSS_1, 10000); // 10 sec
			events.ScheduleEvent(EVENT_ROCK_MOSS_2, 25000); // 25 sec
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
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
				case EVENT_ROCK_MOSS_1:
					DoCastVictim(SPELL_ROCK_MOSS_MURKY_CLOUD);
					events.ScheduleEvent(EVENT_ROCK_MOSS_1, 10000); // 10 sec
					break;
				case EVENT_ROCK_MOSS_2:
					DoCastVictim(SPELL_ROCK_MOSS_RENEWING_MISTS);
					events.ScheduleEvent(EVENT_ROCK_MOSS_2, 25000); // 25 sec
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
		return new npc_RockMossAI(creature);
	}
};

/*################### NPC Jakur of Ordon 73169 ######################*/

enum SpellJakurOfOrdon
{
	SPELL_JAKUR_OF_ORDON_CRACKING_BLOW = 147674,
	SPELL_JAKUR_OF_ORDON_DEFENSIVE_SHIELD = 147689,
};

enum EventJakurOfOrdon
{
	EVENT_JAKUR_OF_ORDON_1 = 1,
	EVENT_JAKUR_OF_ORDON_2 = 2,
};

class npc_JakurOfOrdon : public CreatureScript
{
public:
	npc_JakurOfOrdon() : CreatureScript("npc_JakurOfOrdon") { }

	struct npc_JakurOfOrdonAI : public BossAI
	{
		npc_JakurOfOrdonAI(Creature* creature) : BossAI(creature, 0)
		{
		}

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_JAKUR_OF_ORDON_1, 10000); // 10 sec
			events.ScheduleEvent(EVENT_JAKUR_OF_ORDON_2, 20000); // 20 sec
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
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
				case EVENT_JAKUR_OF_ORDON_1:
					DoCastVictim(SPELL_JAKUR_OF_ORDON_CRACKING_BLOW);
					events.ScheduleEvent(EVENT_JAKUR_OF_ORDON_1, 10000); // 10 sec
					break;
				case EVENT_JAKUR_OF_ORDON_2:
					DoCastVictim(SPELL_JAKUR_OF_ORDON_DEFENSIVE_SHIELD);
					events.ScheduleEvent(EVENT_JAKUR_OF_ORDON_2, 20000); // 20 sec
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
		return new npc_JakurOfOrdonAI(creature);
	}
};

/*################### NPC Watcher Osu 73170 ######################*/

enum SpellWatcherOsu
{
	SPELL_WATCHER_OSU_PYROBLAST = 147720,
	SPELL_WATCHER_OSU_FALLING_FLAMES = 147723,
};

enum EventWatcherOsu
{
	EVENT_WATCHER_OSU_1 = 1,
	EVENT_WATCHER_OSU_2 = 2,
};

class npc_WatcherOsu : public CreatureScript
{
public:
	npc_WatcherOsu() : CreatureScript("npc_WatcherOsu") { }

	struct npc_WatcherOsuAI : public BossAI
	{
		npc_WatcherOsuAI(Creature* creature) : BossAI(creature, 0)
		{
		}

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_WATCHER_OSU_1, 10000); // 10 sec
			events.ScheduleEvent(EVENT_WATCHER_OSU_2, 30000); // 30 sec
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
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
				case EVENT_WATCHER_OSU_1:
					DoCastVictim(SPELL_WATCHER_OSU_PYROBLAST);
					events.ScheduleEvent(EVENT_WATCHER_OSU_1, 10000); // 10 sec
					break;
				case EVENT_WATCHER_OSU_2:
					DoCastVictim(SPELL_WATCHER_OSU_FALLING_FLAMES);
					events.ScheduleEvent(EVENT_WATCHER_OSU_2, 30000); // 30 sec
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
		return new npc_WatcherOsuAI(creature);
	}
};

/*################### NPC Garnia 73282 ######################*/

enum SpellGarnia
{
	SPELL_GARNIA_RUBY_BOLT = 147896,
};

enum EventGarnia
{
	EVENT_GARNIA_1 = 1,
};

class npc_Garnia : public CreatureScript
{
public:
	npc_Garnia() : CreatureScript("npc_Garnia") { }

	struct npc_GarniaAI : public BossAI
	{
		npc_GarniaAI(Creature* creature) : BossAI(creature, 0)
		{
		}

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_GARNIA_1, 10000); // 10 sec
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
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
				case EVENT_GARNIA_1:
					DoCastVictim(SPELL_GARNIA_RUBY_BOLT);
					events.ScheduleEvent(EVENT_GARNIA_1, 10000); // 10 sec
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
		return new npc_GarniaAI(creature);
	}
};

/*################### NPC Bufo 72775 ######################*/

enum SpellBufo
{
	SPELL_BUFO_GULP_FROG_TOXINE = 147655,
};

enum EventBufo
{
	EVENT_BUFO_1 = 1,
};

class npc_Bufo : public CreatureScript
{
public:
	npc_Bufo() : CreatureScript("npc_Bufo") { }

	struct npc_BufoAI : public BossAI
	{
		npc_BufoAI(Creature* creature) : BossAI(creature, 0)
		{
		}

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_BUFO_1, 3000); // 3 sec
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
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
				case EVENT_BUFO_1:
					DoCastVictim(SPELL_BUFO_GULP_FROG_TOXINE);
					events.ScheduleEvent(EVENT_BUFO_1, 3000); // 10 sec
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
		return new npc_BufoAI(creature);
	}
};

/*################### NPC Leafmender 73277 ######################*/

enum SpellLeafmender
{
	SPELL_LEAFMENDER_GREAT_WRATH = 147562,
	SPELL_LEAFMENDER_SUN_WORSHIP = 147565,
	SPELL_LEAFMENDER_HEALING_TOUCH = 147563,
};

enum EventLeafmender
{
	EVENT_LEAFMENDER_1 = 1,
	EVENT_LEAFMENDER_2 = 2,
	EVENT_LEAFMENDER_3 = 3,
};

class npc_Leafmender : public CreatureScript
{
public:
	npc_Leafmender() : CreatureScript("npc_Leafmender") { }

	struct npc_LeafmenderAI : public BossAI
	{
		npc_LeafmenderAI(Creature* creature) : BossAI(creature, 0)
		{
		}

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_LEAFMENDER_1, 10000); // 10 sec
			events.ScheduleEvent(EVENT_LEAFMENDER_2, 20000); // 20 sec
			events.ScheduleEvent(EVENT_LEAFMENDER_3, 30000); // 30 sec
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
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
				case EVENT_LEAFMENDER_1:
					DoCastVictim(SPELL_LEAFMENDER_GREAT_WRATH);
					events.ScheduleEvent(EVENT_LEAFMENDER_1, 10000); // 10 sec
					break;
				case EVENT_LEAFMENDER_2:
					DoCastVictim(SPELL_LEAFMENDER_SUN_WORSHIP);
					events.ScheduleEvent(EVENT_LEAFMENDER_2, 20000); // 20 sec
					break;
				case EVENT_LEAFMENDER_3:
					DoCastVictim(SPELL_LEAFMENDER_HEALING_TOUCH);
					events.ScheduleEvent(EVENT_LEAFMENDER_3, 30000); // 30 sec
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
		return new npc_LeafmenderAI(creature);
	}
};

/*################### NPC Huolon The Black Wind 73167 ######################*/

enum SpellHuolon
{
	SPELL_HUOLON_LIGHTNING_BREATH = 147826,
	SPELL_HUOLON_STORM_BLOSSOM = 147828,
};

enum EventHuolon
{
	EVENT_HUOLON_1 = 1,
	EVENT_HUOLON_2 = 2,
};

class npc_Huolon : public CreatureScript
{
public:
	npc_Huolon() : CreatureScript("npc_Huolon") { }

	struct npc_HuolonAI : public BossAI
	{
		npc_HuolonAI(Creature* creature) : BossAI(creature, 0)
		{
		}

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_HUOLON_1, 10000); // 10 sec
			events.ScheduleEvent(EVENT_HUOLON_2, 30000); // 30 sec
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
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
				case EVENT_HUOLON_1:
					DoCastVictim(SPELL_HUOLON_STORM_BLOSSOM);
					events.ScheduleEvent(EVENT_HUOLON_1, 10000); // 10 sec
					break;
				case EVENT_HUOLON_2:
					DoCastVictim(SPELL_HUOLON_LIGHTNING_BREATH);
					events.ScheduleEvent(EVENT_HUOLON_2, 30000); // 30 sec
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
		return new npc_HuolonAI(creature);
	}
};

/*################### NPC Cinderfall 73175 ######################*/

enum SpellCinderfall
{
	SPELL_CINDERFALL_MOLTEN_INFERNO = 147878,
};

enum EventCinderfall
{
	EVENT_CINDERFALL_1 = 1,
};

class npc_Cinderfall : public CreatureScript
{
public:
	npc_Cinderfall() : CreatureScript("npc_Cinderfall") { }

	struct npc_CinderfallAI : public BossAI
	{
		npc_CinderfallAI(Creature* creature) : BossAI(creature, 0)
		{
		}

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_CINDERFALL_1, 20000); // 20 sec
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
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
				case EVENT_CINDERFALL_1:
					DoCastVictim(SPELL_CINDERFALL_MOLTEN_INFERNO);
					events.ScheduleEvent(EVENT_CINDERFALL_1, 20000); // 20 sec
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
		return new npc_CinderfallAI(creature);
	}
};

/*###################Ordos####################*/
enum Texts
{
	SAY_AGGRO           = 0, // Ordos yells: You will take my place on the eternal brazier.
	SAY_DEATH           = 1, // Ordos yells: The eternal fire will never be extinguished.
	SAY_SLAY            = 2, // Ordos yells: Up in smoke.
	SAY_ANCIENT_FLAME   = 3, // Ordos yells: Your flesh will melt.
	SAY_ETERNAL_AGONY   = 4, // Ordos yells: Your pain will be endless.
	SAY_POOL_OF_FIRE    = 5, // Ordos Yells: You will feel but a fraction of my agony.
	SAY_BURNING_SOUL    = 6, // Ordos Yells: Burn!
};

enum Spells
{
	SPELL_ANCIENT_FLAME  = 144695, // 40 SEC AFTER PULL
	SPELL_BURNING_SOUL   = 144689, // 20 SEC AFTER PULL // NEXT: 30 SEC LATER
	SPELL_ETERNAL_AGONY  = 144696, // ENRAGE SPELL AFTER 5 MINUTES
	SPELL_MAGMA_CRUSH    = 144688, // 10 SEC AFTER PULL // NEXT: 15 SEC LATER
	SPELL_POOL_OF_FIRE   = 144692  // 30 SEC AFTER PULL
};

enum Events
{
	EVENT_ANCIENT_FLAME = 1,
	EVENT_BURNING_SOUL  = 2,
	EVENT_POOL_OF_FIRE  = 3,
	EVENT_MAGMA_CRUSH   = 4,
	EVENT_ETERNAL_AGONY = 5
};

class boss_ordos : public CreatureScript
{
public:
	boss_ordos() : CreatureScript("boss_ordos") { }

	struct boss_ordosAI : public ScriptedAI
	{
		boss_ordosAI(Creature* creature) : ScriptedAI(creature)
		{
		}

		void Reset()
		{
			_events.ScheduleEvent(EVENT_MAGMA_CRUSH, urand(10000, 13000)); // 10-13

			_events.ScheduleEvent(EVENT_ANCIENT_FLAME, urand(40000, 45000)); // 40-45

			_events.ScheduleEvent(EVENT_BURNING_SOUL, urand(20000, 30000)); // 20-30

			_events.ScheduleEvent(EVENT_POOL_OF_FIRE, urand(30000, 45000)); // 30-40
		}

		void KilledUnit(Unit* victim)
		{
			Talk(SAY_SLAY);
		}

		void JustDied(Unit* /*killer*/)
		{
			Talk(SAY_DEATH);
		}

		void EnterCombat(Unit* /*who*/)
		{
			_events.ScheduleEvent(EVENT_ETERNAL_AGONY, 300000); // ENRAGE SPELL AFTER 5 MINUTES
			Talk(SAY_AGGRO);
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim())
			return;

			_events.Update(diff);

			if (me->HasUnitState(UNIT_STATE_CASTING))
				return;

			while (uint32 eventId = _events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_ETERNAL_AGONY:
					Talk(SAY_ETERNAL_AGONY);
					DoCastVictim(SPELL_ETERNAL_AGONY);
					_events.ScheduleEvent(EVENT_ETERNAL_AGONY, urand(10000, 25000));
					break;
				case EVENT_ANCIENT_FLAME:
					Talk(SAY_ANCIENT_FLAME);
					DoCast(me, SPELL_ANCIENT_FLAME);
					_events.ScheduleEvent(EVENT_ANCIENT_FLAME, urand(40000, 45000));
					break;
				case EVENT_POOL_OF_FIRE:
					Talk(SAY_POOL_OF_FIRE);
					DoCast(me, SPELL_POOL_OF_FIRE);
					_events.ScheduleEvent(EVENT_POOL_OF_FIRE, urand(30000, 40000));
					break;
				case EVENT_MAGMA_CRUSH:
					DoCastVictim(SPELL_MAGMA_CRUSH);
					_events.ScheduleEvent(EVENT_MAGMA_CRUSH, urand(7000, 27000));
					break;
				case EVENT_BURNING_SOUL:
					Talk(SAY_BURNING_SOUL);
					DoCastVictim(SPELL_BURNING_SOUL);
					_events.ScheduleEvent(EVENT_BURNING_SOUL, urand(10000, 25000));
					break;
				default:
					break;
				}
			}
			DoMeleeAttackIfReady();
		}

	private:
		EventMap _events;
	};

	CreatureAI* GetAI(Creature* creature) const
	{
		return new boss_ordosAI(creature);
	}
};

/*################### NPC Death Adder ######################*/

enum SpellDeathAdder
{
	DEATH_ADDER_HUGE_FANG = 147289,
};

enum EventDeathAdder
{
	EVENT_DEATH_ADDER_1 = 1,
};

enum Currency
{
	TIMELESS_COIN = 777,
};

class npc_DeathAdder : public CreatureScript
{
public:
	npc_DeathAdder() : CreatureScript("npc_DeathAdder") { }

	struct npc_DeathAdderAI : public BossAI
	{
		npc_DeathAdderAI(Creature* creature) : BossAI(creature, 0)
		{
		}

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_DEATH_ADDER_1, 5000); // 5 sec
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
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
				case EVENT_DEATH_ADDER_1:
					DoCastVictim(DEATH_ADDER_HUGE_FANG);
					events.ScheduleEvent(EVENT_DEATH_ADDER_1, 5000); // 5 sec
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
		return new npc_DeathAdderAI(creature);
	}
};

/*################### NPC Ancient Spineclaw ######################*/

enum SpellAncientSpineclaw
{
	ANCIENT_SPINECLAW_CLAW_FLURRY = 147557,
};

enum EventAncientSpineclaw
{
	EVENT_ANCIENT_SPINE_CLAW_1 = 1,
};

class npc_AncientSpineclaw : public CreatureScript
{
public:
	npc_AncientSpineclaw() : CreatureScript("npc_AncientSpineclaw") { }

	struct npc_AncientSpineclawAI : public BossAI
	{
		npc_AncientSpineclawAI(Creature* creature) : BossAI(creature, 0)
		{
		}

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_ANCIENT_SPINE_CLAW_1, 10000); // 10 sec
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
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
				case EVENT_ANCIENT_SPINE_CLAW_1:
					DoCastVictim(ANCIENT_SPINECLAW_CLAW_FLURRY);
					events.ScheduleEvent(EVENT_ANCIENT_SPINE_CLAW_1, 10000); // 10 sec
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
		return new npc_AncientSpineclawAI(creature);
	}
};

/*################### NPC Great Turtle ######################*/

enum SpellGreatTurtle
{
	GREAT_TURTLE_SHELL_SPIN     = 147571,
	GREAT_TURTLE_SNAPPING_BITE = 147568,
};

enum EventGreatTurtle
{
	EVENT_GREAT_TURTLE_1 = 1,
	EVENT_GREAT_TURTLE_2 = 2,
};

class npc_GreatTurtle : public CreatureScript
{
public:
	npc_GreatTurtle() : CreatureScript("npc_GreatTurtle") { }

	struct npc_GreatTurtleAI : public BossAI
	{
		npc_GreatTurtleAI(Creature* creature) : BossAI(creature, 0)
		{
		}

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_GREAT_TURTLE_1, 10000); // 10 sec
			events.ScheduleEvent(EVENT_GREAT_TURTLE_2, 30000); // 30 sec
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
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
				case EVENT_GREAT_TURTLE_1:
					DoCastVictim(GREAT_TURTLE_SNAPPING_BITE);
					events.ScheduleEvent(EVENT_GREAT_TURTLE_1, 10000); // 10 sec
					break;
				case EVENT_GREAT_TURTLE_2:
					DoCastVictim(GREAT_TURTLE_SHELL_SPIN);
					events.ScheduleEvent(EVENT_GREAT_TURTLE_2, 30000); // 30 sec
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
		return new npc_GreatTurtleAI(creature);
	}
};

/*################### NPC Archiereus of Flame ######################*/

enum SpellArchiereusofFlame
{
	ARCHIEREUS_OF_FLAME_BLAZING_BLOW = 148003,
	ARCHIEREUS_OF_FLAME_FIRE_STORM = 147998,
	ARCHIEREUS_OF_FLAME_CAUTERIZE = 147997,
};

enum EventArchiereusofFlame
{
	EVENT_ARCHIEREUS_OF_FLAME_1 = 1,
	EVENT_ARCHIEREUS_OF_FLAME_2 = 2,
	EVENT_ARCHIEREUS_OF_FLAME_3 = 3,
};

class npc_ArchiereusofFlame : public CreatureScript
{
public:
	npc_ArchiereusofFlame() : CreatureScript("npc_ArchiereusofFlame") { }

	struct npc_ArchiereusofFlameAI : public BossAI
	{
		npc_ArchiereusofFlameAI(Creature* creature) : BossAI(creature, 0)
		{
		}

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_ARCHIEREUS_OF_FLAME_1, 10000); // 10 sec
			events.ScheduleEvent(EVENT_ARCHIEREUS_OF_FLAME_2, 30000); // 30 sec
			events.ScheduleEvent(EVENT_ARCHIEREUS_OF_FLAME_3, 60000); // 60 sec
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
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
				case EVENT_ARCHIEREUS_OF_FLAME_1:
					DoCastVictim(ARCHIEREUS_OF_FLAME_BLAZING_BLOW);
					events.ScheduleEvent(EVENT_ARCHIEREUS_OF_FLAME_1, 10000); // 10 sec
					break;
				case EVENT_ARCHIEREUS_OF_FLAME_2:
					DoCastVictim(ARCHIEREUS_OF_FLAME_FIRE_STORM);
					events.ScheduleEvent(EVENT_ARCHIEREUS_OF_FLAME_2, 30000); // 30 sec
					break;
				case EVENT_ARCHIEREUS_OF_FLAME_3:
					DoCastVictim(ARCHIEREUS_OF_FLAME_CAUTERIZE);
					events.ScheduleEvent(EVENT_ARCHIEREUS_OF_FLAME_3, 60000); // 60 sec
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
		return new npc_ArchiereusofFlameAI(creature);
	}
};

/*################### NPC Blazebound Chanter ######################*/

enum SpellBlazeboundChanter
{
	BLAZEBOUND_CHANTER_GREATER_PYROBLAST = 148002,
	BLAZEBOUND_CHANTER_FIRE_STORM = 147998,
	BLAZEBOUND_CHANTER_CAUTERIZE = 147997,
};

enum EventBlazeboundChanter
{
	EVENT_BLAZEBOUND_CHANTER_1 = 1,
	EVENT_BLAZEBOUND_CHANTER_2 = 2,
	EVENT_BLAZEBOUND_CHANTER_3 = 3,
};

class npc_BlazeboundChanter : public CreatureScript
{
public:
	npc_BlazeboundChanter() : CreatureScript("npc_BlazeboundChanter") { }

	struct npc_BlazeboundChanterAI : public BossAI
	{
		npc_BlazeboundChanterAI(Creature* creature) : BossAI(creature, 0)
		{
		}

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_BLAZEBOUND_CHANTER_1, 10000); // 10 sec
			events.ScheduleEvent(EVENT_BLAZEBOUND_CHANTER_2, 30000); // 30 sec
			events.ScheduleEvent(EVENT_BLAZEBOUND_CHANTER_3, 60000); // 60 sec
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
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
				case EVENT_BLAZEBOUND_CHANTER_1:
					DoCastVictim(BLAZEBOUND_CHANTER_GREATER_PYROBLAST);
					events.ScheduleEvent(EVENT_BLAZEBOUND_CHANTER_1, 10000); // 10 sec
					break;
				case EVENT_BLAZEBOUND_CHANTER_2:
					DoCastVictim(BLAZEBOUND_CHANTER_FIRE_STORM);
					events.ScheduleEvent(EVENT_BLAZEBOUND_CHANTER_2, 30000); // 30 sec
					break;
				case EVENT_BLAZEBOUND_CHANTER_3:
					DoCastVictim(BLAZEBOUND_CHANTER_CAUTERIZE);
					events.ScheduleEvent(EVENT_BLAZEBOUND_CHANTER_3, 60000); // 60 sec
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
		return new npc_BlazeboundChanterAI(creature);
	}
};

/*################### NPC Ashleaf Sprite ######################*/

enum SpellAshleafSprite
{
	ASHLEAF_SPRITE_GREAT_WRATH = 147562,
	ASHLEAF_SPRITE_HEALING_TOUCH = 147563,
	ASHLEAF_SPRITE_SUN_WORSHIP = 147565,
};

enum EventAshleafSprite
{
	EVENT_ASHLEAF_SPRITE_1 = 1,
	EVENT_ASHLEAF_SPRITE_2 = 2,
	EVENT_ASHLEAF_SPRITE_3 = 3,
};

class npc_AshleafSprite : public CreatureScript
{
public:
	npc_AshleafSprite() : CreatureScript("npc_AshleafSprite") { }

	struct npc_AshleafSpriteAI : public BossAI
	{
		npc_AshleafSpriteAI(Creature* creature) : BossAI(creature, 0)
		{
		}

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_ASHLEAF_SPRITE_1, 10000); // 10 sec
			events.ScheduleEvent(EVENT_ASHLEAF_SPRITE_2, 30000); // 30 sec
			events.ScheduleEvent(EVENT_ASHLEAF_SPRITE_3, 60000); // 60 sec
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
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
				case EVENT_ASHLEAF_SPRITE_1:
					DoCastVictim(ASHLEAF_SPRITE_GREAT_WRATH);
					events.ScheduleEvent(EVENT_ASHLEAF_SPRITE_1, 10000); // 10 sec
					break;
				case EVENT_ASHLEAF_SPRITE_2:
					DoCastVictim(ASHLEAF_SPRITE_SUN_WORSHIP);
					events.ScheduleEvent(EVENT_ASHLEAF_SPRITE_2, 30000); // 30 sec
					break;
				case EVENT_ASHLEAF_SPRITE_3:
					DoCastVictim(ASHLEAF_SPRITE_HEALING_TOUCH);
					events.ScheduleEvent(EVENT_ASHLEAF_SPRITE_3, 60000); // 60 sec
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
		return new npc_AshleafSpriteAI(creature);
	}
};

/*################### NPC Eternal Kilnmaster ######################*/

enum SpellEternalKilnmaster
{
	ETERNAL_KILNMASTER_FIERY_CHARGE = 147704,
	ETERNAL_KILNMASTER_BLAZING_BLOW = 148003,
	ETERNAL_KILNMASTER_CONJURE_ETERNAL_KILN = 148004,
	ETERNAL_KILNMASTER_ICE_TRAP = 135382,
};

enum EventEternalKilnmaster
{
	EVENT_ETERNAL_KILNMASTER_1 = 1,
	EVENT_ETERNAL_KILNMASTER_2 = 2,
	EVENT_ETERNAL_KILNMASTER_3 = 3,
};

class npc_EternalKilnmaster : public CreatureScript
{
public:
	npc_EternalKilnmaster() : CreatureScript("npc_EternalKilnmaster") { }

	struct npc_EternalKilnmasterAI : public BossAI
	{
		npc_EternalKilnmasterAI(Creature* creature) : BossAI(creature, 0)
		{
		}

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			DoCastVictim(ETERNAL_KILNMASTER_FIERY_CHARGE);
			events.ScheduleEvent(EVENT_ETERNAL_KILNMASTER_1, 10000); // 10 sec
			events.ScheduleEvent(EVENT_ETERNAL_KILNMASTER_2, 30000); // 30 sec
			events.ScheduleEvent(EVENT_ETERNAL_KILNMASTER_3, 60000); // 60 sec
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
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
				case EVENT_ETERNAL_KILNMASTER_1:
					DoCastVictim(ETERNAL_KILNMASTER_BLAZING_BLOW);
					events.ScheduleEvent(EVENT_ETERNAL_KILNMASTER_1, 10000); // 10 sec
					break;
				case EVENT_ETERNAL_KILNMASTER_2:
					DoCastVictim(ETERNAL_KILNMASTER_ICE_TRAP);
					events.ScheduleEvent(EVENT_ETERNAL_KILNMASTER_2, 30000); // 30 sec
					break;
				case EVENT_ETERNAL_KILNMASTER_3:
					DoCastVictim(ETERNAL_KILNMASTER_CONJURE_ETERNAL_KILN);
					events.ScheduleEvent(EVENT_ETERNAL_KILNMASTER_3, 60000); // 60 sec
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
		return new npc_EternalKilnmasterAI(creature);
	}
};

/*################### NPC Brilliant Windfeather ######################*/

enum SpellBrilliantWindfeather
{
	BRILLIANT_WINDFEATHER_GUST_OF_WIND = 147310,
	BRILLIANT_WINDFEATHER_LULLABY = 126246,
};

enum EventBrilliantWindfeather
{
	EVENT_BRILLIANT_WINDFEATHER_1 = 1,
	EVENT_BRILLIANT_WINDFEATHER_2 = 2,
};

class npc_BrilliantWindfeather : public CreatureScript
{
public:
	npc_BrilliantWindfeather() : CreatureScript("npc_BrilliantWindfeather") { }

	struct npc_BrilliantWindfeatherAI : public BossAI
	{
		npc_BrilliantWindfeatherAI(Creature* creature) : BossAI(creature, 0)
		{
		}

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_BRILLIANT_WINDFEATHER_1, 10000); // 10 sec
			events.ScheduleEvent(EVENT_BRILLIANT_WINDFEATHER_2, 30000); // 30 sec
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
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
				case EVENT_BRILLIANT_WINDFEATHER_1:
					DoCastVictim(BRILLIANT_WINDFEATHER_LULLABY);
					events.ScheduleEvent(EVENT_BRILLIANT_WINDFEATHER_1, 10000); // 10 sec
					break;
				case EVENT_BRILLIANT_WINDFEATHER_2:
					DoCastVictim(BRILLIANT_WINDFEATHER_GUST_OF_WIND);
					events.ScheduleEvent(EVENT_BRILLIANT_WINDFEATHER_2, 30000); // 30 sec
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
		return new npc_BrilliantWindfeatherAI(creature);
	}
};

/*################### NPC Burning Berserker ######################*/

enum SpellBurningBerserker
{
	BURNING_BERSERKER_FIERY_CHARGE = 147704,
	BURNING_BERSERKER_BRUNING_FURY = 147703,
	BURNING_BERSERKER_BLAZING_CLEAVE = 147702,
};

enum EventBurningBerserker
{
	EVENT_BURNING_BERSERKER_1 = 1,
	EVENT_BURNING_BERSERKER_2 = 2,
};

class npc_BurningBerserker : public CreatureScript
{
public:
	npc_BurningBerserker() : CreatureScript("npc_BurningBerserker") { }

	struct npc_BurningBerserkerAI : public BossAI
	{
		npc_BurningBerserkerAI(Creature* creature) : BossAI(creature, 0)
		{
		}

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_BURNING_BERSERKER_1, 10000); // 10 sec
			events.ScheduleEvent(EVENT_BURNING_BERSERKER_2, 20000); // 20 sec
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
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
				case EVENT_BURNING_BERSERKER_1:
					DoCastVictim(BURNING_BERSERKER_BRUNING_FURY);
					events.ScheduleEvent(EVENT_BURNING_BERSERKER_1, 10000); // 10 sec
					break;
				case EVENT_BURNING_BERSERKER_2:
					DoCastVictim(BURNING_BERSERKER_BLAZING_CLEAVE);
					events.ScheduleEvent(EVENT_BURNING_BERSERKER_2, 20000); // 20 sec
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
		return new npc_BurningBerserkerAI(creature);
	}
};

/*################### NPC Ordon Oathguard ######################*/

enum SpellOrdonOathguard
{
	ORDON_OATHGUARD_CRACKING_BLOW = 147674,
	ORDON_OATHGUARD_DEFENSIVE_SHIELD = 147689,
};

enum EventOrdonOathguard
{
	EVENT_ORDON_OATHGUARD_1 = 1,
	EVENT_ORDON_OATHGUARD_2 = 2,
};

class npc_OrdonOathguard : public CreatureScript
{
public:
	npc_OrdonOathguard() : CreatureScript("npc_OrdonOathguard") { }

	struct npc_OrdonOathguardAI : public BossAI
	{
		npc_OrdonOathguardAI(Creature* creature) : BossAI(creature, 0)
		{
		}

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_ORDON_OATHGUARD_1, 10000); // 10 sec
			events.ScheduleEvent(EVENT_ORDON_OATHGUARD_2, 20000); // 20 sec
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
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
				case EVENT_ORDON_OATHGUARD_1:
					DoCastVictim(ORDON_OATHGUARD_CRACKING_BLOW);
					events.ScheduleEvent(EVENT_ORDON_OATHGUARD_1, 10000); // 10 sec
					break;
				case EVENT_ORDON_OATHGUARD_2:
					DoCastVictim(ORDON_OATHGUARD_DEFENSIVE_SHIELD);
					events.ScheduleEvent(EVENT_ORDON_OATHGUARD_2, 20000); // 20 sec
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
		return new npc_OrdonOathguardAI(creature);
	}
};

/*################### NPC Ordon Candlekeeper ######################*/

enum SpellOrdonCandlekeeper
{
	ORDON_CANDLEKEEPER_BREATH_OF_FIRE = 147416,
};

enum EventOrdonCandlekeeper
{
	EVENT_ORDON_CANDLEKEEPER_1 = 1,
};

class npc_OrdonCandlekeeper : public CreatureScript
{
public:
	npc_OrdonCandlekeeper() : CreatureScript("npc_OrdonCandlekeeper") { }

	struct npc_OrdonCandlekeeperAI : public BossAI
	{
		npc_OrdonCandlekeeperAI(Creature* creature) : BossAI(creature, 0)
		{
		}

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_ORDON_CANDLEKEEPER_1, 10000); // 10 sec
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
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
				case EVENT_ORDON_CANDLEKEEPER_1:
					DoCastVictim(ORDON_CANDLEKEEPER_BREATH_OF_FIRE);
					events.ScheduleEvent(EVENT_ORDON_CANDLEKEEPER_1, 20000); // 20 sec
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
		return new npc_OrdonCandlekeeperAI(creature);
	}
};

/*################### NPC Ordon Fire-Watcher ######################*/

enum SpellOrdonFireWatcher
{
	FIRE_WATCHER_PYROBLAST = 147720,
	FIRE_WATCHER_FALLING_FLAMES = 147723,
};

enum EventOrdonFireWatcher
{
	EVENT_ORDON_FIRE_WATCHER_1 = 1,
	EVENT_ORDON_FIRE_WATCHER_2 = 2,
};

class npc_OrdonFireWatcher : public CreatureScript
{
public:
	npc_OrdonFireWatcher() : CreatureScript("npc_OrdonFireWatcher") { }

	struct npc_OrdonFireWatcherAI : public BossAI
	{
		npc_OrdonFireWatcherAI(Creature* creature) : BossAI(creature, 0)
		{
		}

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_ORDON_FIRE_WATCHER_1, 10000); // 10 sec
			events.ScheduleEvent(EVENT_ORDON_FIRE_WATCHER_2, 20000); // 20 sec
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
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
				case EVENT_ORDON_FIRE_WATCHER_1:
					DoCastVictim(FIRE_WATCHER_PYROBLAST);
					events.ScheduleEvent(EVENT_ORDON_FIRE_WATCHER_1, 10000); // 10 sec
					break;
				case EVENT_ORDON_FIRE_WATCHER_2:
					DoCastVictim(FIRE_WATCHER_FALLING_FLAMES);
					events.ScheduleEvent(EVENT_ORDON_FIRE_WATCHER_2, 20000); // 20 sec
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
		return new npc_OrdonFireWatcherAI(creature);
	}
};

/*################### NPC Gulp Frog ######################*/

enum SpellGulpFrog
{
	GULP_FROG_TOXIN = 147655,
};

enum EventGulpFrog
{
	EVENT_GULP_FROG_1 = 1,
};

class npc_GulpFrog : public CreatureScript
{
public:
	npc_GulpFrog() : CreatureScript("npc_GulpFrog") { }

	struct npc_GulpFrogAI : public BossAI
	{
		npc_GulpFrogAI(Creature* creature) : BossAI(creature, 0)
		{
		}

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_GULP_FROG_1, 5000); // 5 sec
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
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
				case EVENT_GULP_FROG_1:
					DoCastVictim(GULP_FROG_TOXIN);
					events.ScheduleEvent(EVENT_GULP_FROG_1, 5000); // 5 sec
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
		return new npc_GulpFrogAI(creature);
	}
};

/*################### NPC Crag Stalker ######################*/

enum SpellCragStalker
{
	CRAG_STALKER_POUNCE = 147649,
	CRAG_STALKER_RENDING_SWIPE = 147646,
};

enum EventCragStalker
{
	EVENT_CRAG_STALKER_1 = 1,
	EVENT_CRAG_STALKER_2 = 2,
};

class npc_CragStalker : public CreatureScript
{
public:
	npc_CragStalker() : CreatureScript("npc_CragStalker") { }

	struct npc_CragStalkerAI : public BossAI
	{
		npc_CragStalkerAI(Creature* creature) : BossAI(creature, 0)
		{
		}

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_CRAG_STALKER_1, 10000); // 10 sec
			events.ScheduleEvent(EVENT_CRAG_STALKER_2, 20000); // 20 sec
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
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
				case EVENT_CRAG_STALKER_1:
					DoCastVictim(CRAG_STALKER_POUNCE);
					events.ScheduleEvent(EVENT_CRAG_STALKER_1, 10000); // 10 sec
					break;
				case EVENT_CRAG_STALKER_2:
					DoCastVictim(CRAG_STALKER_RENDING_SWIPE);
					events.ScheduleEvent(EVENT_CRAG_STALKER_2, 20000); // 20 sec
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
		return new npc_CragStalkerAI(creature);
	}
};

/*################### NPC Primal Stalker ######################*/

enum SpellPrimalStalker
{
	PRIMAL_STALKER_POUNCE = 147649,
	PRIMAL_STALKER_RENDING_SWIPE = 147646,
};

enum EventPrimalStalker
{
	EVENT_PRIMAL_STALKER_1 = 1,
	EVENT_PRIMAL_STALKER_2 = 2,
};

class npc_PrimalStalker : public CreatureScript
{
public:
	npc_PrimalStalker() : CreatureScript("npc_PrimalStalker") { }

	struct npc_PrimalStalkerAI : public BossAI
	{
		npc_PrimalStalkerAI(Creature* creature) : BossAI(creature, 0)
		{
		}

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_PRIMAL_STALKER_1, 10000); // 10 sec
			events.ScheduleEvent(EVENT_PRIMAL_STALKER_2, 20000); // 20 sec
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
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
				case EVENT_PRIMAL_STALKER_1:
					DoCastVictim(PRIMAL_STALKER_POUNCE);
					events.ScheduleEvent(EVENT_PRIMAL_STALKER_1, 10000); // 10 sec
					break;
				case EVENT_PRIMAL_STALKER_2:
					DoCastVictim(PRIMAL_STALKER_RENDING_SWIPE);
					events.ScheduleEvent(EVENT_PRIMAL_STALKER_2, 20000); // 20 sec
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
		return new npc_PrimalStalkerAI(creature);
	}
};

/*################### NPC Ironfur Great Bull ######################*/

enum SpellIronfurGreatBull
{
	IRONFUR_GREAT_BULL_OX_CHARGE = 147386,
	IRONFUR_GREAT_BULL_IRON_FUR = 147368,
};

enum EventIronfurGreatBull
{
	EVENT_IRONFUR_GREAT_BULL_1 = 1,
	EVENT_IRONFUR_GREAT_BULL_2 = 2,
};

class npc_IronfurGreatBull : public CreatureScript
{
public:
	npc_IronfurGreatBull() : CreatureScript("npc_IronfurGreatBull") { }

	struct npc_IronfurGreatBullAI : public BossAI
	{
		npc_IronfurGreatBullAI(Creature* creature) : BossAI(creature, 0)
		{
		}

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_IRONFUR_GREAT_BULL_1, 10000); // 10 sec
			events.ScheduleEvent(EVENT_IRONFUR_GREAT_BULL_2, 20000); // 20 sec
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
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
				case EVENT_IRONFUR_GREAT_BULL_1:
					DoCastVictim(IRONFUR_GREAT_BULL_OX_CHARGE);
					events.ScheduleEvent(EVENT_IRONFUR_GREAT_BULL_1, 10000); // 10 sec
					break;
				case EVENT_IRONFUR_GREAT_BULL_2:
					DoCastVictim(IRONFUR_GREAT_BULL_IRON_FUR);
					events.ScheduleEvent(EVENT_IRONFUR_GREAT_BULL_2, 20000); // 20 sec
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
		return new npc_IronfurGreatBullAI(creature);
	}
};

/*################### NPC Jademist Dancer ######################*/

enum SpellJademistDancer
{
	JADEMIST_DANCER_STEAM_BLAST = 147863,
};

enum EventJademistDancer
{
	EVENT_JADEMIST_DANCER_1 = 1,
};

class npc_JademistDancer : public CreatureScript
{
public:
	npc_JademistDancer() : CreatureScript("npc_JademistDancer") { }

	struct npc_JademistDancerAI : public BossAI
	{
		npc_JademistDancerAI(Creature* creature) : BossAI(creature, 0)
		{
		}

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_JADEMIST_DANCER_1, 10000); // 10 sec
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
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
				case EVENT_JADEMIST_DANCER_1:
					DoCastVictim(JADEMIST_DANCER_STEAM_BLAST);
					events.ScheduleEvent(EVENT_JADEMIST_DANCER_1, 10000); // 10 sec
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
		return new npc_JademistDancerAI(creature);
	}
};

/*################### NPC Spectral Windwalker ######################*/

enum SpellSpectralWindwalker
{
	SPECTRAL_WINDWALKER_CHI_BURST = 148729,
};

enum EventSpectralWindwalker
{
	EVENT_SPECTRAL_WINDWALKER_1 = 1,
};

class npc_SpectralWindwalker : public CreatureScript
{
public:
	npc_SpectralWindwalker() : CreatureScript("npc_SpectralWindwalker") { }

	struct npc_SpectralWindwalkerAI : public BossAI
	{
		npc_SpectralWindwalkerAI(Creature* creature) : BossAI(creature, 0)
		{
		}

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_SPECTRAL_WINDWALKER_1, 10000); // 10 sec
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
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
				case EVENT_SPECTRAL_WINDWALKER_1:
					DoCastVictim(SPECTRAL_WINDWALKER_CHI_BURST);
					events.ScheduleEvent(EVENT_SPECTRAL_WINDWALKER_1, 10000); // 10 sec
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
		return new npc_SpectralWindwalkerAI(creature);
	}
};

/*################### NPC Spectral Brewmaster ######################*/

enum SpellSpectralBrewmaster
{
	SPECTRAL_BREWMASTER_SPINNING_CRANE_KICK = 148730,
};

enum EventSpectralBrewmaster
{
	EVENT_SPECTRAL_BREWMASTER_1 = 1,
};

class npc_SpectralBrewmaster : public CreatureScript
{
public:
	npc_SpectralBrewmaster() : CreatureScript("npc_SpectralBrewmaster") { }

	struct npc_SpectralBrewmasterAI : public BossAI
	{
		npc_SpectralBrewmasterAI(Creature* creature) : BossAI(creature, 0)
		{
		}

		void Reset()
		{
			_Reset();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_SPECTRAL_BREWMASTER_1, 10000); // 10 sec
		}

		void KilledUnit(Unit * /*victim*/)
		{
		}

		void JustDied(Unit * /*victim*/)
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
				case EVENT_SPECTRAL_BREWMASTER_1:
					DoCastVictim(SPECTRAL_BREWMASTER_SPINNING_CRANE_KICK);
					events.ScheduleEvent(EVENT_SPECTRAL_BREWMASTER_1, 10000); // 10 sec
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
		return new npc_SpectralBrewmasterAI(creature);
	}
};

class Item_Curious_Bronze_Timepiece_ally : public ItemScript
{
public:

	Item_Curious_Bronze_Timepiece_ally() : ItemScript("Item_Curious_Bronze_Timepiece_ally"){ }

	bool OnUse(Player* player, Item* /*item*/, SpellCastTargets const& /*targets*/)
	{
		player->CastSpell(player, 147988);
		player->TeleportTo(870, -901.09f, -4640.38f, 5.25f, 3.11f);
		return true;
	}
};

class Item_Curious_Bronze_Timepiece_horde : public ItemScript
{
public:

	Item_Curious_Bronze_Timepiece_horde() : ItemScript("Item_Curious_Bronze_Timepiece_horde"){ }

	bool OnUse(Player* player, Item* /*item*/, SpellCastTargets const& /*targets*/)
	{
		player->CastSpell(player, 147985);
		player->TeleportTo(870, -403.99f, -4606.47f, 4.08f, 3.56f);
		return true;
	}
};

enum flamecore
{
	RARE_ARCHIEREUS_OF_FLAME = 73174,
	RARE_URDUR_THE_CAUTERIZER = 73173,
	NPC_BLAZEBOUND_CHANTER = 72897,
	NPC_HIGH_PRIEST_OF_ORDOS = 72898,
	RARE_FLINTLORD_GAIRAN = 73172,
	NPC_ETERNAL_KILNMASTER = 72896,
	SPELL_KILNFIRE = 152178,
};

class npc_eternal_kiln : public CreatureScript
{
	public:npc_eternal_kiln() : CreatureScript("npc_eternal_kiln") { }
  
		   struct npc_eternal_kilnAI : public ScriptedAI
		   {
			   npc_eternal_kilnAI(Creature* creature) : ScriptedAI(creature) { }

			   void JustDied(Unit* /*killer*/)
			   {
				   me->DespawnOrUnsummon();
			   }

			   void IsSummonedBy(Unit* summoner)
			   {
				   switch (summoner->GetEntry())
				   {
				   case RARE_ARCHIEREUS_OF_FLAME:
				   case RARE_FLINTLORD_GAIRAN:
				   case NPC_ETERNAL_KILNMASTER:
				   case NPC_HIGH_PRIEST_OF_ORDOS:
					   DoCast(summoner, SPELL_KILNFIRE);
					   me->SetReactState(REACT_PASSIVE);
					   break;
				   default:
					   break;
				   }
			   }
		   };

		CreatureAI* GetAI(Creature* creature) const
		{
			return new npc_eternal_kilnAI(creature);
		}
};

class npc_flarecore_golem : public CreatureScript
{
public: npc_flarecore_golem() : CreatureScript("npc_flarecore_golem") { }

	struct npc_flarecore_golemAI : public ScriptedAI
	{
	npc_flarecore_golemAI(Creature* creature) : ScriptedAI(creature) { }
	
		void JustDied(Unit* /*killer*/)
		{
		me->DespawnOrUnsummon();
		}
	
		void IsSummonedBy(Unit* summoner)
		{
		switch (summoner->GetEntry())
			{
			case RARE_ARCHIEREUS_OF_FLAME:
			case RARE_URDUR_THE_CAUTERIZER:
			case NPC_BLAZEBOUND_CHANTER:
			case NPC_HIGH_PRIEST_OF_ORDOS:
				 me->SetWalk(true);
				 me->GetMotionMaster()->MoveChase(summoner->getVictim(), 0.0f, 0.0f);
				 me->SetInCombatWith(summoner->getVictim());
				 me->SetReactState(REACT_AGGRESSIVE);
				 break;
			default:
				break;
		}
	}
};

	CreatureAI* GetAI(Creature* creature) const
	{
	return new npc_flarecore_golemAI(creature);
	}
};

void AddSC_Zone_TimelessIsle()
{
	new npc_eternal_kiln(); // 72896
	new npc_flarecore_golem(); // 73527
	new npc_Zesqua();
	new npc_Spelurk();
	new npc_Karkanos();
	new npc_EmeraldGander();
	new npc_GreatTurtleFuryshell();
	new npc_SpiritOfJadefire();
	new npc_IronfurSteelhorn();
	new npc_Chelon();
	new npc_Tsavoka();
	new npc_ImperialPython();
	new npc_MonstrousSpineclaw();
	new npc_RockMoss();
	new npc_JakurOfOrdon();
	new npc_WatcherOsu();
	new npc_Garnia();
	new npc_Bufo();
	new npc_Leafmender();
	new npc_Huolon();
	new npc_Cinderfall();
	new npc_SpectralBrewmaster();
	new npc_SpectralWindwalker();
	new npc_JademistDancer();
	new npc_IronfurGreatBull();
	new npc_PrimalStalker();
	new npc_CragStalker();
	new npc_GulpFrog();
	new npc_OrdonFireWatcher();
	new npc_OrdonCandlekeeper();
	new npc_OrdonOathguard();
	new npc_BurningBerserker();
	new npc_BrilliantWindfeather();
	new npc_EternalKilnmaster();
	new npc_AshleafSprite();
	new npc_BlazeboundChanter();
	new npc_ArchiereusofFlame();
	new npc_GreatTurtle();
	new npc_AncientSpineclaw();
	new npc_DeathAdder();
	new boss_ordos();
	new Item_Curious_Bronze_Timepiece_ally();
	new Item_Curious_Bronze_Timepiece_horde();
}