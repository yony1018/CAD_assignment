#include <GLFW/glfw3.h>

#include "EulerOperator.hpp"

using namespace std;

void DrawSolid(Solid *_solid, const bool _line = false);
void DrawFace(Face *_face, const bool _line);
void DrawLoop(Loop *_loop);


void DrawSolid(Solid *_solid, const bool _line)
{
    Face *startF = _solid->sFace;
    Face *f = _solid->sFace;
    do
    {
        if (f != nullptr)
            DrawFace(f, _line);
        f = f->nextF;
    } while (nullptr != f && f != startF);
}

void DrawFace(Face *_face, const bool _line)
{
    Loop *startL;
    Loop *l;


    startL = _face->fLoop;
    l = _face->fLoop;
    do
    {
        if (l != nullptr && l->isInnerLoop())
            DrawLoop(l);
        l = l->nextL;
    } while (nullptr != l && l != startL);

    // 画出外环
    startL = _face->fLoop;
    l = _face->fLoop;
    do
    {
        if (l != nullptr && !l->isInnerLoop())
            DrawLoop(l);
        l = l->nextL;
    } while (nullptr != l && l != startL);
    if (!_line)
    {
        glDisable(GL_STENCIL_TEST);
    }
}

void DrawLoop(Loop *_loop)
{

    glBegin(GL_LINE_LOOP); 
    HalfEdge *startHe = _loop->lHalfEdge;
    HalfEdge *he = _loop->lHalfEdge;
    Vertex *startV = he->startV;
    do
    {
        glm::vec3 point = he->startV->point->p;
        glm::vec3 color = he->startV->point->color;
        glColor3f(1, 0, 0); 
        glVertex3f(point.x, point.y, point.z);
        he = he->nextHe;
    } while (nullptr != he && he != startHe);
    glEnd();
}
