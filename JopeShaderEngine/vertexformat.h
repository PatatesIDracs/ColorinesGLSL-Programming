#ifndef VERTEXFORMAT_H
#define VERTEXFORMAT_H

#define MAX_VERTEX_ATTRIBUTES 8

struct VertexAttribute
{
    bool enabled = false;
    int offset = 0;
    int ncomp = 0;
};

class VertexFormat
{
public:

    void SetVertexAttribute(int location, int offset, int ncomp)
    {
        attributes[location].enabled = true;
        attributes[location].offset = offset;
        attributes[location].ncomp = ncomp;

        size += ncomp * sizeof(float);
    }

    VertexAttribute attributes[MAX_VERTEX_ATTRIBUTES];
    int size = 0;
};


#endif // VERTEXFORMAT_H
