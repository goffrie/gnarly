CXX=g++
CXXFLAGS=-Wall -MMD -ggdb -std=gnu++11 -I. -Ilevelobject -Ilevelobject/related -Ilevelobject/player -Ilevelobject/monster -Idungeongen -Ilevelobject/related/skills -Ipopup
LDFLAGS=-lncurses
EXEC=gnarly
OBJECTS=\
	levelobject/related/skills/skill.o \
	levelobject/related/skills/stealth.o \
	levelobject/related/skills/heal.o \
	levelobject/related/skills/divinemight.o \
	levelobject/related/skills/doublestrike.o \
	levelobject/related/skills/fireball.o \
	levelobject/related/skills/mindcontrol.o \
	levelobject/related/attributes.o \
	levelobject/related/attributedecorator.o \
	levelobject/related/basicbuff.o \
	levelobject/related/classbuff.o \
	levelobject/related/class.o \
	levelobject/related/thief.o \
	levelobject/related/paladin.o \
	levelobject/related/wizard.o \
	levelobject/player/player.o \
	levelobject/player/humanplayer.o \
	levelobject/player/dwarfplayer.o \
	levelobject/player/elfplayer.o \
	levelobject/player/orcplayer.o \
	levelobject/monster/monster.o \
	levelobject/monster/merchant.o \
	levelobject/monster/dragon.o \
	levelobject/levelobject.o \
	levelobject/character.o \
	levelobject/potion.o \
	levelobject/gold.o \
	levelobject/dragongold.o \
	levelobject/staircase.o \
	dungeongen/dungeongen.o \
	dungeongen/bspgen.o \
	dungeongen/aggregationgen.o \
	shadowcasting/intervalset.o \
	shadowcasting/shadowcast.o \
	popup/popup.o \
	surface.o \
	ui.o \
	util.o \
	basicui.o \
	cursesui.o \
	levelobjectvisitor.o \
	game.o \
	dungeon.o \
	display.o \
	displayable.o \
	playerstatus.o \
	level.o \
	memory.o \
	main.o \
	team.o \
	commandargs.o \
	direction.o \
	playerselect.o \
	target.o \
	basicspawn.o
DEPENDS=${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} ${LDFLAGS}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm -f ${OBJECTS} ${EXEC} ${DEPENDS}
