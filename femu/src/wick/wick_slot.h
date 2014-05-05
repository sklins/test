#pragma once
#include <util/global.h>
#include <feyn/particle.h>

class TWickSlot
{
    public:
        friend class TWickTask;
        friend class TInteraction;
        friend class TCorrelation;
        //friend void TCorrelation::Solve(QVector<TDiagram*> *output);
        TWickSlot(uint32_t equivalenceClass, uint32_t inconsistencyMask, bool allowSimpleLoops = false, bool correlation = false);
        TWickSlot();
    
    public:
        static bool EquivalentSlots(const TWickSlot &a, const TWickSlot &b);
        static bool AllowContraction(const TWickSlot &a, const TWickSlot &b, TParticle* particleType);
        static void Contract(TWickSlot &a, TWickSlot &b, TParticle* particleType);
        static void BreakContraction(TWickSlot &a, TWickSlot &b, TParticle* particleType);
        void InitializeFreedomDegree(TParticle* particleType, uint32_t count);
        bool IsFinalized() const;
        TParticle* GetPendingParticleType() const;
    
    private:
        QHash<TParticle*, uint32_t> InitialFreedomDegrees;
        QHash<TParticle*, uint32_t> CurrentFreedomDegrees;

        uint32_t EquivalenceClass;
        uint32_t InconsistencyMask;
        bool AllowSimpleLoops;
        bool Correlation;
};
