#include "EulerOperator.hpp"
// 五种基本欧拉操作与扫掠操作

Solid *mvfs(Point point, Vertex *&vertex)
{
    //开辟变量空间
    Solid *ob = new Solid();
    Face *f = new Face();
    Loop *lp = new Loop();

    vertex = new Vertex();
    vertex->point = new Point();
    vertex->point->SetPoint(point);

    //为变量成员赋值来实现欧拉操作
    ob->sFace = f;
    f->fSolid = ob;
    f->fLoop = lp;
    lp->lFace = f;

    return ob;
}

// 构造一个新点，同时构造一条连接新点和给定点的边
HalfEdge *mev(Vertex *vertex, Point point, Loop *lp)
{
    // 开辟空间
    HalfEdge *he1 = new HalfEdge();
    HalfEdge *he2 = new HalfEdge();
    Edge *newEdge = new Edge();

    newEdge->firstHe = he1;
    newEdge->secondHe = he2;
    he1->edge = newEdge;
    he2->edge = newEdge;
    he1->adjacentHe = he2;
    he2->adjacentHe = he1;

    Vertex *newVertex = new Vertex();
    newVertex->point = new Point();
    newVertex->point->SetPoint(point);

    he1->startV = vertex;
    he1->endV = newVertex;
    he2->startV = newVertex;
    he2->endV = vertex;

    he1->heLoop = lp;
    he2->heLoop = lp;

    he1->nextHe = he2;
    he2->prevHe = he1;
    if (nullptr == lp->lHalfEdge)
    {
        he2->nextHe = he1;
        he1->prevHe = he2;
        lp->lHalfEdge = he1;
    }
    else
    {
        HalfEdge *he;
        for (he = lp->lHalfEdge; he->nextHe->startV != vertex; he = he->nextHe)
        {
        }
        he2->nextHe = he->nextHe;
        he->nextHe->prevHe = he2;

        he1->prevHe = he;
        he->nextHe = he1;
    }

    Solid *oldSolid = lp->lFace->fSolid;
    Edge *e = oldSolid->edgeList;
    if (nullptr == e)
    {
        oldSolid->edgeList = newEdge;
    }
    else
    {
        while (e->nextE != nullptr)
        {
            e = e->nextE;
        }
        e->nextE = newEdge;
        newEdge->prevE = e;
    }
    return he1;
}

Loop *mef(Vertex *v1, Vertex *v2, Loop *&old_loop)
{

    HalfEdge *he1 = new HalfEdge();
    HalfEdge *he2 = new HalfEdge();
    Edge *newEdge = new Edge();

    newEdge->firstHe = he1;
    newEdge->secondHe = he2;
    he1->edge = newEdge;
    he2->edge = newEdge;
    he1->adjacentHe = he2;
    he2->adjacentHe = he1;

    he1->startV = v1;
    he1->endV = v2;
    he2->startV = v2;
    he2->endV = v1;

    HalfEdge *he;
    HalfEdge *startHE;
    int isRepeatLoop;

    startHE = he = old_loop->lHalfEdge;
    isRepeatLoop = 0;
    for (he = old_loop->lHalfEdge; he->startV != v1; he = he->nextHe)
    {
        if (he == startHE && isRepeatLoop == 2)
        {
            cout << "mef failed: cannot find v1 : " << *(v1->point) << "." << endl;
            return nullptr;
        }
        if (he == startHE && isRepeatLoop != 2)
        {
            isRepeatLoop++;
        }
    }
    HalfEdge *firstHalfEdge = he;

    startHE = he = old_loop->lHalfEdge;
    isRepeatLoop = 0;
    for (he = old_loop->lHalfEdge; he->startV != v2; he = he->nextHe)
    {
        if (he == startHE && isRepeatLoop == 2)
        {
            cout << "mef failed: cannot find v2 : " << *(v2->point) << "." << endl;
            return nullptr;
        }
        if (he == startHE && isRepeatLoop != 2)
        {
            isRepeatLoop++;
        }
    }
    HalfEdge *secondHalfEdge = he;

    he2->nextHe = firstHalfEdge;
    he2->prevHe = secondHalfEdge->prevHe;
    he1->nextHe = secondHalfEdge;
    he1->prevHe = firstHalfEdge->prevHe;
    firstHalfEdge->prevHe->nextHe = he1;
    firstHalfEdge->prevHe = he2;
    secondHalfEdge->prevHe->nextHe = he2;
    secondHalfEdge->prevHe = he1;

    old_loop->lHalfEdge = he1;
    Loop *newLoop = new Loop();
    newLoop->lHalfEdge = he2;

    Solid *oldSolid = old_loop->lFace->fSolid;

    Face *newFace = new Face();
    newFace->fLoop = newLoop;
    newLoop->lFace = newFace;
    newFace->fSolid = oldSolid;

    Face *f;
    for (f = oldSolid->sFace; f->nextF != nullptr; f = f->nextF)
    {
    }
    f->nextF = newFace;
    newFace->prevF = f;

    Edge *e = oldSolid->edgeList;
    if (nullptr == e)
    {
        oldSolid->edgeList = newEdge;
    }
    else
    {
        while (e->nextE != nullptr)
        {
            e = e->nextE;
        }
        e->nextE = newEdge;
        newEdge->prevE = e;
    }
    if (newLoop->size() > old_loop->size())
    {
        swapLoop(newLoop, old_loop);
    }
    return newLoop;
}

Loop *kemr(Vertex *v1, Vertex *v2, Loop *&old_loop)
{
    Loop *newLoop = new Loop();

    HalfEdge *he;
    for (he = old_loop->lHalfEdge; !(v1 == he->startV && v2 == he->endV); he = he->nextHe){;}

    Edge *e = he->edge;
    he->nextHe->prevHe = he->adjacentHe->prevHe;
    he->adjacentHe->prevHe->nextHe = he->nextHe;

    he->prevHe->nextHe = he->adjacentHe->nextHe;
    he->adjacentHe->nextHe->prevHe = he->prevHe;

    old_loop->lHalfEdge = he->prevHe;
    newLoop->lHalfEdge = he->nextHe;

    Face *oldFace = old_loop->lFace;
    newLoop->lFace = oldFace;

    Loop *lp;
    for (lp = oldFace->fLoop; nullptr != lp->nextL; lp = lp->nextL){;}
    lp->nextL = newLoop;
    newLoop->prevL = lp;

    Solid *oldSolid = old_loop->lFace->fSolid;
    e = oldSolid->edgeList;
    if (e == he->edge)
    {
        oldSolid->edgeList = he->edge->nextE;
        oldSolid->edgeList->prevE = e->prevE;
    }
    else
    {
        while (e->nextE != he->edge)
        {
            e = e->nextE;
        }
        e->nextE = he->edge->nextE;
        e->nextE->prevE = e;
    }
    if (newLoop->size() > old_loop->size())
    {
        swapLoop(newLoop, old_loop);
    }
    return newLoop;
}

void kfmrh(Loop *_outter_loop, Loop *inner_loop)
{
    Face *face_1 = _outter_loop->lFace;
    Face *face_2 = inner_loop->lFace;

    Loop *lp;
    for (lp = face_1->fLoop; nullptr != lp->nextL; lp = lp->nextL)
    {
    }
    lp->nextL = inner_loop;
    inner_loop->prevL = lp;
    inner_loop->lFace = face_1;


    Solid *oldSolid = face_1->fSolid;
    Face *f = oldSolid->sFace;
    if (f == face_2)
    {
        oldSolid->sFace = f->nextF;
        oldSolid->sFace->prevF = f->prevF;
    }
    else
    {
        while (f->nextF != face_2)
        {
            f = f->nextF;
        }
        f->nextF = face_2->nextF;
        f->nextF->prevF = f;
    }

    return;
}

Solid *sweep(Face *_face, glm::vec3 direction, float distance)
{
    Solid *solid = _face->fSolid;
    Loop *loop;
    HalfEdge *he;
    for (loop = _face->fLoop; loop != nullptr; loop = loop->nextL)
    {
        he = loop->lHalfEdge;
        Vertex *startV = he->startV;
        glm::vec3 newPosition = startV->point->p + distance * direction;
        Point newPoint(newPosition.x, newPosition.y, newPosition.z);

        HalfEdge *firstConnectHe = mev(startV, newPoint, loop);
        Vertex *upVertex_1 = firstConnectHe->endV;

        he = he->nextHe;
        Vertex *v = he->startV;
        while (v != startV) 
        {
            glm::vec3 newPosition = v->point->p + distance * direction;
            Point newPoint(newPosition.x, newPosition.y, newPosition.z);
            
            HalfEdge *connectHe = mev(v, newPoint, loop);
            Vertex *upVertex_2 = connectHe->endV;
            mef(upVertex_2, upVertex_1, loop);
            upVertex_1 = upVertex_2;
            he = he->nextHe;
            v = he->startV;
        }
        mef(firstConnectHe->endV, upVertex_1, loop);
    }
    return solid;
}

void swapLoop(Loop *&_loop_1, Loop *&_loop_2)
{
    Loop *temp = _loop_1;
    _loop_1 = _loop_2;
    _loop_2 = temp;
}


int Face::size()
{
    if (fLoop == nullptr)
    {
        return 0;
    }
    else
    {
        int count = 0;
        Loop *startL = fLoop;
        Loop *l = fLoop;
        do
        {
            count++;
            l = l->nextL;
        } while (nullptr != l && l != startL);
        return count;
    }
}

int Loop::size()
{
    if (lHalfEdge == nullptr)
    {
        return 0;
    }
    else
    {
        int count = 0;
        HalfEdge *startHe = lHalfEdge;
        HalfEdge *he = lHalfEdge;
        do
        {
            count++;
            he = he->nextHe;
        } while (nullptr != he && he != startHe);
        return count;
    }
}