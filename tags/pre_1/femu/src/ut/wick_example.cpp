#include <ut/tests.h>
#include "wick_example.h"
#include <wick/wick_slot.h>
#include <wick/wick_task.h>

void GenerateContractionsForSampleTask() {
    uint32_t const scalarBoson = 0;

    TWickSlot inputBoson1(1, 1, 1);
    inputBoson1.InitializeFreedomDegree(scalarBoson, 1);

    TWickSlot inputBoson2(1, 1, 1);
    inputBoson2.InitializeFreedomDegree(scalarBoson, 1);

    TWickSlot ouputBoson1(1, 2, 2);
    ouputBoson1.InitializeFreedomDegree(scalarBoson, 1);
    
    TWickSlot ouputBoson2(1, 2, 2);
    ouputBoson2.InitializeFreedomDegree(scalarBoson, 1);

    TWickSlot F4Vertex1(1, 3, 0, true);
    F4Vertex1.InitializeFreedomDegree(scalarBoson, 4);
    
    // Uncomment this if you want another interaction vertex
    // TWickSlot F4Vertex2(1, 4, 0, true);
    // F4Vertex2.InitializeFreedomDegree(scalarBoson, 4);

    TWickTask task;
    task.Slots << inputBoson1 << inputBoson2 << ouputBoson1 << ouputBoson2;
    task.Slots << F4Vertex1;

    // And this
    // task.Slots << F4Vertex2;

    task.Solve();
}
