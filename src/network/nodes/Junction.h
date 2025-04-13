#pragma once
#include "Vertex.h"
#include <vector>

class Junction :
    public Vertex
{
    std::vector<Edge*> m_in;
    std::vector<Edge*> m_out;

public:
    Junction(Vector2 position);
    std::vector<Edge*> in() const;
    std::vector<Edge*> out() const;
    bool canAddIn() override;
    bool canAddOut() override;
    bool addIn(Edge* inEdge) override;
    bool addOut(Edge* outEdge) override;
    bool removeIn(Edge* inEdge) override;
    bool removeOut(Edge* outEdge) override;
};

