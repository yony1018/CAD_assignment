#pragma once
// 构建一个 8 字 Brep 实体

#include <GLFW/glfw3.h>

#include "EulerOperator.hpp"

void DrawSolid(Solid *_solid, const bool _line = false);
void DrawFace(Face *_face, const bool _line);
void DrawLoop(Loop *_loop);

Solid *CreateSolid()
{
    Solid *new_solid;

    Vertex *topUpperLeft;
    new_solid = mvfs(Point(-1.0, 0.5, 2.0), topUpperLeft);
    Loop *topLoop = new_solid->sFace->fLoop;
    HalfEdge *topUpperHalfEdge = mev(topUpperLeft, Point(1.0, 0.5, 2.0), topLoop);
    Vertex *topUpperRight = topUpperHalfEdge->endV;
    HalfEdge *topLeftHalfEdge = mev(topUpperLeft, Point(-1.0, 0.5, -2.0), topLoop);
    Vertex *topBottomLeft = topLeftHalfEdge->endV;
    HalfEdge *topRightHalfEdge = mev(topUpperRight, Point(1.0, 0.5, -2.0), topLoop);
    Vertex *topBottomRight = topRightHalfEdge->endV;
    // Make top ring
    Loop *downLoop = mef(topBottomLeft, topBottomRight, topLoop);

    HalfEdge *upperLeftHalfEdge = mev(topUpperLeft, Point(-1.0, -0.5, 2.0), downLoop);
    Vertex *downUpperLeft = upperLeftHalfEdge->endV;
    HalfEdge *upperRightHalfEdge = mev(topUpperRight, Point(1.0, -0.5, 2.0), downLoop);
    Vertex *downUpperRight = upperRightHalfEdge->endV;
    HalfEdge *bottomLeftHalfEdge = mev(topBottomLeft, Point(-1.0, -0.5, -2.0), downLoop);
    Vertex *downBottomLeft = bottomLeftHalfEdge->endV;
    HalfEdge *bottomRightHalfEdge = mev(topBottomRight, Point(1.0, -0.5, -2.0), downLoop);
    Vertex *downBottomRight = bottomRightHalfEdge->endV;

    Loop *upperLoop = mef(downUpperLeft, downUpperRight, downLoop);
    Loop *rightLoop = mef(downUpperRight, downBottomRight, downLoop);
    Loop *bottomLoop = mef(downBottomRight, downBottomLeft, downLoop);
    Loop *leftLoop = mef(downBottomLeft, downUpperLeft, downLoop);


    HalfEdge *topBridge = mev(topUpperLeft, Point(-0.5, 0.5, 1.5), topLoop);
    Vertex *topInnerUpperLeft = topBridge->endV;

    HalfEdge *topInnerUpperHalfEdge = mev(topInnerUpperLeft, Point(0.5, 0.5, 1.5), topLoop);
    Vertex *topInnerUpperRight = topInnerUpperHalfEdge->endV;
    HalfEdge *topInnerRightHalfEdge = mev(topInnerUpperRight, Point(0.5, 0.5, 0.5), topLoop);
    Vertex *topInnerBottomRight = topInnerRightHalfEdge->endV;
    HalfEdge *topInnerLeftHalfEdge = mev(topInnerUpperLeft, Point(-0.5, 0.5, 0.5), topLoop);
    Vertex *topInnerBottomLeft = topInnerLeftHalfEdge->endV;
    Loop *downInnerLoop = mef(topInnerBottomLeft, topInnerBottomRight, topLoop);

    Loop *topInnerLoop = kemr(topUpperLeft, topInnerUpperLeft, topLoop);

    HalfEdge *upperLeftInnerHalfEdge = mev(topInnerUpperLeft, Point(-0.5, -0.5, 1.5), downInnerLoop);
    Vertex *downInnerUpperLeft = upperLeftInnerHalfEdge->endV;
    HalfEdge *upperRightInnerHalfEdge = mev(topInnerUpperRight, Point(0.5, -0.5, 1.5), downInnerLoop);
    Vertex *downInnerUpperRight = upperRightInnerHalfEdge->endV;
    HalfEdge *bottomLeftInnerHalfEdge = mev(topInnerBottomLeft, Point(-0.5, -0.5, 0.5), downInnerLoop);
    Vertex *downInnerBottomLeft = bottomLeftInnerHalfEdge->endV;
    HalfEdge *bottomRightInnerHalfEdge = mev(topInnerBottomRight, Point(0.5, -0.5, 0.5), downInnerLoop);
    Vertex *downInnerBottomRight = bottomRightInnerHalfEdge->endV;

    Loop *upperInnerLoop = mef(downInnerUpperLeft, downInnerUpperRight, downInnerLoop);
    Loop *rightInnerLoop = mef(downInnerUpperRight, downInnerBottomRight, downInnerLoop);
    Loop *bottomInnerLoop = mef(downInnerBottomRight, downInnerBottomLeft, downInnerLoop);
    Loop *leftInnerLoop = mef(downInnerBottomLeft, downInnerUpperLeft, downInnerLoop);

    kfmrh(downLoop, downInnerLoop);

    topInnerLoop->SetInnerLoop(true);
    downInnerLoop->SetInnerLoop(true);

    HalfEdge *topBridge2 = mev(topUpperLeft, Point(-0.5, 0.5, -0.5), topLoop);
    Vertex *topInnerUpperLeft2 = topBridge2->endV;

    HalfEdge *topInnerUpperHalfEdge2 = mev(topInnerUpperLeft2, Point(0.5, 0.5, -0.5), topLoop);
    Vertex *topInnerUpperRight2 = topInnerUpperHalfEdge2->endV;
    HalfEdge *topInnerRightHalfEdge2 = mev(topInnerUpperRight2, Point(0.5, 0.5, -1.5), topLoop);
    Vertex *topInnerBottomRight2 = topInnerRightHalfEdge2->endV;
    HalfEdge *topInnerLeftHalfEdge2 = mev(topInnerUpperLeft2, Point(-0.5, 0.5, -1.5), topLoop);
    Vertex *topInnerBottomLeft2 = topInnerLeftHalfEdge2->endV;
    Loop *downInnerLoop2 = mef(topInnerBottomLeft2, topInnerBottomRight2, topLoop);

    Loop *topInnerLoop2 = kemr(topUpperLeft, topInnerUpperLeft2, topLoop);

    HalfEdge *upperLeftInnerHalfEdge2 = mev(topInnerUpperLeft2, Point(-0.5, -0.5, -0.5), downInnerLoop2);
    Vertex *downInnerUpperLeft2 = upperLeftInnerHalfEdge2->endV;
    HalfEdge *upperRightInnerHalfEdge2 = mev(topInnerUpperRight2, Point(0.5, -0.5, -0.5), downInnerLoop2);
    Vertex *downInnerUpperRight2 = upperRightInnerHalfEdge2->endV;
    HalfEdge *bottomLeftInnerHalfEdge2 = mev(topInnerBottomLeft2, Point(-0.5, -0.5, -1.5), downInnerLoop2);
    Vertex *downInnerBottomLeft2 = bottomLeftInnerHalfEdge2->endV;
    HalfEdge *bottomRightInnerHalfEdge2 = mev(topInnerBottomRight2, Point(0.5, -0.5, -1.5), downInnerLoop2);
    Vertex *downInnerBottomRight2 = bottomRightInnerHalfEdge2->endV;

    Loop *upperInnerLoop2 = mef(downInnerUpperLeft2, downInnerUpperRight2, downInnerLoop2);
    Loop *rightInnerLoop2 = mef(downInnerUpperRight2, downInnerBottomRight2, downInnerLoop2);
    Loop *bottomInnerLoop2 = mef(downInnerBottomRight2, downInnerBottomLeft2, downInnerLoop2);
    Loop *leftInnerLoop2 = mef(downInnerBottomLeft2, downInnerUpperLeft2, downInnerLoop2);

    kfmrh(downLoop, downInnerLoop2);

    topInnerLoop2->SetInnerLoop(true);
    downInnerLoop2->SetInnerLoop(true);

    return new_solid;
}
