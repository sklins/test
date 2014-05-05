#include "correlation.h"
#include "limitations.h"
#include <wick/wick_task.h>

void TCorrelation::SetToZero(uint32_t &totalSum)
{
    for (QSet<TInteraction*>::Iterator i = FeynRules->Interactions.begin(); i != FeynRules->Interactions.end(); i++)
    {
        CurLimits[*i] = 0;
    }
    if (!IncludeKinematics)
    {
        CurLimits[(CurLimits.end() - 1).key()] = 1;
        totalSum++;
    }
}

//проверяет, является ли текущая комбинация количества вершин последней
//т.е. не равно ли количество вершин каждого типа максимуму
bool TCorrelation::LastCombination()
{
    for (QSet<TInteraction*>::Iterator i = FeynRules->Interactions.begin(); i != FeynRules->Interactions.end(); i++)
    {
        if (CurLimits[*i] < this->Limitations->InteractionLimits[*i])
            return false;
    }
    return true;
}

//если сумма вершин равна лимиту, то сразу обнуляет последний разряд, увеличивая предпоследний
//по идее, должно работать, ибо больше лимита становиться не будет
//а что делать, если из-за неё не достигнется комбинация, состоящая из максимумов - тогда же цикл не остановится
//или остановится?
bool TCorrelation::NormalTotalSum(uint32_t &totalSum)
{
    QHash<TInteraction*, uint32_t>::Iterator i = CurLimits.end() - 1;
    if (totalSum >= this->Limitations->TotalInteractionLimit)
    {
        totalSum -= i.value();
        i.value() = 0;
        return false;
    }
    return true;
}

//генерит следующую комбинацию
void TCorrelation::NextCombination(uint32_t &totalSum)
{
    QHash<TInteraction*, uint32_t>::Iterator it = CurLimits.end() - 1;
    it.value()++;
    totalSum++;
    while (it.value() == this->Limitations->InteractionLimits[it.key()])
    {
        totalSum += it.value();
        it.value() = 0;
        it--;
        it.value()++;
        totalSum++;
    }
}

//тут хуета, потому что не прописываю ни масок, ни классов эквив, вообще ни хера
//а как, ёпту? они уже созданы, поля эти прайват
//а главное, какие значения-то должны быть
void TCorrelation::ToWickTask(TWickTask* wickTask)
{
    for (QHash<TInteraction*, uint32_t>::Iterator i = CurLimits.begin(); i != CurLimits.end(); i++)
    {
        for (uint32_t j = 0; j < i.value(); j++)
        {
            TWickSlot slot;
            wickTask->Slots.push_back(slot);
            i.key()->ExportToSlot(&wickTask->Slots.back(), AllowSimpleLoops);
        }
    }
    //точно так? просто по одной вершине? или всё же рёбра куда-то пилить
    for (QSet<TParticle*>::Iterator i = FeynRules->Particles.begin(); i != FeynRules->Particles.end(); i++)
    {
        TWickSlot slot;
        wickTask->Slots.push_back(slot);
        if (ExternalParticles.contains(*i))
            wickTask->Slots.back().InitializeFreedomDegree(*i, 1);
        else
            wickTask->Slots.back().InitializeFreedomDegree(*i, 0);
        wickTask->Slots.back().Correlation = true;
        wickTask->Slots.back().AllowSimpleLoops = this->AllowSimpleLoops;
    }
}

void TCorrelation::Solve(QVector<TDiagram*> *output)
{
    uint32_t totalSum = 0;
    
    SetToZero(totalSum);
    while (!LastCombination())
    {
        //точно есть баги
        NormalTotalSum(totalSum);
        NextCombination(totalSum);
        
        TWickTask* wickTask = new TWickTask();
        ToWickTask(wickTask);
        wickTask->Solve(output);
    }
}
