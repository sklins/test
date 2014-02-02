#include <ut/tests.h>
#include <wick_contractions/wick_slot.h>

void UT_WickSlot_Contractions_QED() {
    uint32_t const electron = 0;
    uint32_t const photon = 1;

    TWickSlot inputElectron1(2, 1, 1);
    inputElectron1.InitializeFreedomDegree(electron, 1);
    inputElectron1.InitializeFreedomDegree(photon, 0);

    TWickSlot inputElectron2(2, 2, 1);
    inputElectron2.InitializeFreedomDegree(electron, 1);
    inputElectron2.InitializeFreedomDegree(photon, 0);
    
    TWickSlot ouputElectron1(2, 3, 2);
    ouputElectron1.InitializeFreedomDegree(electron, 1);
    ouputElectron1.InitializeFreedomDegree(photon, 0);
    
    TWickSlot ouputElectron2(2, 4, 2);
    ouputElectron2.InitializeFreedomDegree(electron, 1);
    ouputElectron2.InitializeFreedomDegree(photon, 0);
    
    TWickSlot QEDVertex1(2, 5, 0);
    QEDVertex1.InitializeFreedomDegree(electron, 2);
    QEDVertex1.InitializeFreedomDegree(photon, 1);
    
    TWickSlot QEDVertex2(2, 5, 0);
    QEDVertex2.InitializeFreedomDegree(electron, 2);
    QEDVertex2.InitializeFreedomDegree(photon, 1);

    VERIFY(!TWickSlot::EquivalentSlots(inputElectron1, inputElectron2));
    VERIFY(!TWickSlot::EquivalentSlots(ouputElectron1, ouputElectron2));
    VERIFY(!TWickSlot::EquivalentSlots(inputElectron1, ouputElectron1));
    VERIFY(!TWickSlot::EquivalentSlots(inputElectron1, ouputElectron2));
    VERIFY(!TWickSlot::EquivalentSlots(inputElectron1, QEDVertex1));
    VERIFY(TWickSlot::EquivalentSlots(QEDVertex1, QEDVertex2));

    VERIFY(!TWickSlot::AllowConnection(inputElectron1, inputElectron2, electron));
    VERIFY(!TWickSlot::AllowConnection(ouputElectron1, ouputElectron2, electron));
    
    VERIFY(TWickSlot::AllowConnection(inputElectron1, ouputElectron1, electron));
    VERIFY(TWickSlot::AllowConnection(inputElectron1, ouputElectron2, electron));

    VERIFY(TWickSlot::AllowConnection(QEDVertex1, QEDVertex2, photon));
    VERIFY(TWickSlot::AllowConnection(inputElectron1, QEDVertex1, electron));
    VERIFY(!TWickSlot::AllowConnection(inputElectron1, QEDVertex1, photon));
}

void UT_WickSlot() {
    MESSAGE("WickSlot unittest...");
    UT_WickSlot_Contractions_QED();
    MESSAGE("WickSlot unittest: ok");
}
