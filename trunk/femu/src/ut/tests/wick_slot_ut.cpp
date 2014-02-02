#include <ut/tests.h>
#include <wick_contractions/wick_slot.h>

void UT_WickSlot_Contractions() {
    uint32_t const electron = 0;
    uint32_t const photon = 1;

    UNUSED(electron);
    UNUSED(photon);

    TWickSlot inputElectron1(2, 1, 1);
    TWickSlot inputElectron2(2, 2, 1);
    TWickSlot ouputElectron1(2, 3, 2);
    TWickSlot ouputElectron2(2, 4, 2);
    TWickSlot QEDVertex1(2, 5, 0);
    TWickSlot QEDVertex2(2, 5, 0);

    VERIFY(!TWickSlot::EquivalentSlots(inputElectron1, inputElectron2));
    VERIFY(!TWickSlot::EquivalentSlots(ouputElectron1, ouputElectron2));
    VERIFY(!TWickSlot::EquivalentSlots(inputElectron1, ouputElectron1));
    VERIFY(!TWickSlot::EquivalentSlots(inputElectron1, ouputElectron2));
    VERIFY(!TWickSlot::EquivalentSlots(inputElectron1, QEDVertex1));
    VERIFY(TWickSlot::EquivalentSlots(QEDVertex1, QEDVertex2));

    /*
    // TODO: implement TWickSlot::InitializeFreedomDegree(particleType);
    // So we can have non-zero freedom degrees. Then the following should work properly.

    VERIFY(!TWickSlot::AllowConnection(inputElectron1, inputElectron2, electron));
    VERIFY(!TWickSlot::AllowConnection(ouputElectron1, ouputElectron2, electron));
    
    VERIFY(TWickSlot::AllowConnection(inputElectron1, ouputElectron1, electron));
    VERIFY(TWickSlot::AllowConnection(inputElectron1, ouputElectron2, electron));

    VERIFY(TWickSlot::AllowConnection(QEDVertex1, QEDVertex2, photon));
    VERIFY(TWickSlot::AllowConnection(inputElectron1, QEDVertex1, electron));
    VERIFY(!TWickSlot::AllowConnection(inputElectron1, QEDVertex1, photon));
    */
}

void UT_WickSlot() {
    MESSAGE("WickSlot unittest...");
    UT_WickSlot_Contractions();
    MESSAGE("WickSlot unittest: ok");
}
