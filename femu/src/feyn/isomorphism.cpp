#include "isomorphism.h"

typedef QPair<int, int> TSimplifiedEdge;

class TSimplifiedDiagram {
public:
    int N; // Nodes count
    QVector<TSimplifiedEdge> E; // Edges
    QVector<TParticle*> F; // Edge 'flavors'

    static void Simplify(const TDiagram &d, TSimplifiedDiagram *res) {
        QHash<TVertex*, int> ids;
        int id = 0;

        for (QSet<TVertex*>::ConstIterator i = d.Correlations.constBegin();
             i != d.Correlations.constEnd(); i++) {
            ids.insert(*i, id++);
        }

        for (QSet<TVertex*>::ConstIterator i = d.Interactions.constBegin();
             i != d.Interactions.constEnd(); i++) {
            ids.insert(*i, id++);
        }

        res->N = d.Correlations.size() + d.Interactions.size();

        for (QSet<TEdge*>::ConstIterator i = d.Edges.constBegin();
             i != d.Edges.constEnd(); i++) {
            ASSERT(ids.contains((*i)->A) && ids.contains((*i)->B));
            res->E.push_back(TSimplifiedEdge(ids[(*i)->A], ids[(*i)->B]));
            res->F.push_back((*i)->Particle);
        }
    }
};

class TIsomorphismChecker {
public:
    static bool CheckPerm(const TSimplifiedDiagram &a, const TSimplifiedDiagram &b, const QVector<int> &perm) {
        QBitArray usedEdges(b.E.size(), false);
        for (int i = 0; i < a.E.size(); i++) {
            int r = -1;

            for (int j = 0; j < b.E.size(); j++) {
                if (usedEdges[j] || b.F[j] != a.F[i])
                    continue;
                if (
                    (a.E[i].first == perm[b.E[j].first] && a.E[i].second == perm[b.E[j].second])
                        ||
                    (a.E[i].first == perm[b.E[j].second] && a.E[i].second == perm[b.E[j].first])
                   ) { r = j; break; }
            }

            if (r == -1) return false;
            usedEdges[r] = true;
        }
        return true;
    }

    static bool Brute(const TSimplifiedDiagram &a, const TSimplifiedDiagram &b, QVector<int> &perm, int k) {
        if (k == perm.size())
            return CheckPerm(a, b, perm);

        for (int i = 0; i < perm.size(); i++) {
            bool good = true;

            for (int j = 0; j < k; j++) {
                if (perm[j] == i) {
                    good = false;
                    break;
                }
            }

            if (!good) continue;

            perm[k] = i;

            if (Brute(a, b, perm, k + 1))
                return true;
        }
        return false;
    }

    static bool Check(const TSimplifiedDiagram &a, const TSimplifiedDiagram &b) {
        if (a.N != b.N) return false;
        QVector<int> perm(a.N);
        return Brute(a, b, perm, 0);
    }
};

bool CheckIsomorphism(const TDiagram &a, const TDiagram &b) {
    if (a.Correlations.size() != b.Correlations.size()) return false;
    if (a.Interactions.size() != b.Interactions.size()) return false;
    if (a.Edges.size() != b.Edges.size()) return false;

    QHash<TParticle*, int> aEdges, bEdges;
    for (QSet<TEdge*>::ConstIterator i = a.Edges.constBegin(); i != a.Edges.constEnd(); i++)
        aEdges[(*i)->Particle]++;

    for (QSet<TEdge*>::ConstIterator i = b.Edges.constBegin(); i != b.Edges.constEnd(); i++)
        bEdges[(*i)->Particle]++;

    if (aEdges.size() != bEdges.size()) return false;

    for (QHash<TParticle*, int>::ConstIterator i = aEdges.begin(); i != aEdges.end(); i++) {
        if (bEdges[i.key()] != i.value()) return false;
    }

    TSimplifiedDiagram as, bs;
    TSimplifiedDiagram::Simplify(a, &as);
    TSimplifiedDiagram::Simplify(b, &bs);

    return TIsomorphismChecker::Check(as, bs);
}

void FilterDiagrams(const QVector<TDiagram*> *input, QVector<TDiagram*> *output) {
    for (int i = 0; i < input->size(); i++) {
        bool good = true;

        for (int j = 0; j < i; j++) {
            if (CheckIsomorphism(*input->at(i), *input->at(j))) {
                good = false;
                break;
            }
        }

        if (good) {
            output->push_back(input->at(i));
        }
    }
}
