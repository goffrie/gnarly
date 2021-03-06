#include "levelplan.h"

#include "dungeon.h"
#include "constantgen.h"
#include "forestgen.h"
#include "aggregationgen.h"
#include "roomsgen.h"
#include "finalgen.h"

using namespace std;

const LevelPlan& LevelPlan::basicPlan() {
    static const Dungeon defaultDungeon(
        "|-----------------------------------------------------------------------------|\n"
        "|                                                                             |\n"
        "| |--------------------------|        |-----------------------|               |\n"
        "| |..........................|        |.......................|               |\n"
        "| |..........................+########+.......................|-------|       |\n"
        "| |..........................|   #    |...............................|--|    |\n"
        "| |..........................|   #    |..................................|--| |\n"
        "| |----------+---------------|   #    |----+----------------|...............| |\n"
        "|            #                 #############                |...............| |\n"
        "|            #                 #     |-----+------|         |...............| |\n"
        "|            #                 #     |............|         |...............| |\n"
        "|            ###################     |............|   ######+...............| |\n"
        "|            #                 #     |............|   #     |...............| |\n"
        "|            #                 #     |-----+------|   #     |--------+------| |\n"
        "|  |---------+-----------|     #           #          #              #        |\n"
        "|  |.....................|     #           #          #         |----+------| |\n"
        "|  |.....................|     ########################         |...........| |\n"
        "|  |.....................|     #           #                    |...........| |\n"
        "|  |.....................|     #    |------+--------------------|...........| |\n"
        "|  |.....................|     #    |.......................................| |\n"
        "|  |.....................+##########+.......................................| |\n"
        "|  |.....................|          |.......................................| |\n"
        "|  |---------------------|          |---------------------------------------| |\n"
        "|                                                                             |\n"
        "|-----------------------------------------------------------------------------|\n"
    );
    static ConstantGen defaultGen(defaultDungeon);
    static LevelPlan plan(vector<LevelGen*>(8, &defaultGen));

    return plan;
}

const LevelPlan& LevelPlan::gnarlyPlan() {
    static RoomsGen rooms(25, 79);
    static AggregationGen cave(25, 79);
    static RoomsGen outdoor(25, 79, true);
    static ForestGen forest(25, 79);
    static FinalGen final;
    static LevelGen* gens[5] = {
        &rooms, &cave, &outdoor, &forest, &final
    };
    static LevelPlan plan(vector<LevelGen*>(gens, gens+5));

    return plan;
}
