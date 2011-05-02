#include "landscape.h"
#include "propertymanagers.h"
#include "texturesmanager.h"
#include "constants.h"
#include "scene.h"
#include "qgl.h"

static Landscape *singletone = 0;
int dX = 0;
int dY = 0;
int maxX = 0;
int minY = 0;
int minX = 0;

void setBorders(double x, double y, int dH)
{
    if (maxX < x)
        maxX = x;

    if (minY > y)
        minY = y;

    if (minX > x)
        minX = x;

    dX = maxX - minX;
    dY = dH - minY;
}

Landscape::Landscape(QtAbstractPropertyBrowser *propertyBrowser) : BaseObject(propertyBrowser)
{
    setRootName(CORE_GROUP);
    setName(LANDSCAPE_NAME);
    init();

    singletone = this;
    tex = 0;
    lastSize = 0;
    coords = 0;
    lastSelected = 0;

    name->setEnabled(false);
    QtProperty *borders = addNewProperty("Borders", PropertyManagers::getInstance()->getGroupPropertyManager());
    QtProperty *tiling = addNewProperty("Tiling", PropertyManagers::getInstance()->getGroupPropertyManager());
    tX = addNewProperty("X", PropertyManagers::getInstance()->getIntPropertyManager(), tiling);
    tY = addNewProperty("Y", PropertyManagers::getInstance()->getIntPropertyManager(), tiling);
    left = addNewProperty("Left (screens)", PropertyManagers::getInstance()->getIntPropertyManager(), borders);
    right = addNewProperty("Right (screens)", PropertyManagers::getInstance()->getIntPropertyManager(), borders);
    height = addNewProperty("Height (%)", PropertyManagers::getInstance()->getIntPropertyManager(), borders);

    PropertyManagers::getInstance()->getIntPropertyManager()->setRange(height, 0, 100);

    setTexX(1);
    setTexY(1);
    setLeft(0);
    setRight(1);
    setHeight(50);

    connect(PropertyManagers::getInstance()->getIntPropertyManager(), SIGNAL(propertyChanged(QtProperty*)),
                this, SLOT(landscapeHeightChanged(QtProperty*)));
}

void CALLBACK tessVertex(void *vertex)
{
    double *_vertex = (double *)vertex;
    double x = (_vertex[0] - (double)minX) / (double)dX;
    double y = (_vertex[1] - minY) / (double)dY;

    if (singletone != 0) {
        x *= singletone->getTexX();
        y *= singletone->getTexY();
    }

    glTexCoord2d(x, y);
    glVertex2dv(_vertex);
}

void Landscape::paint(QPainter *painter, QPaintEvent *event, Scene *scene)
{
    if (tex == 0)
        tex = TexturesManager::getInstance()->getNone();

    this->scene = scene;
    int height = event->rect().bottom() * 5 / 6;
    worldHeight = scene->getWorldHeight();
    int w_h = worldHeight * scene->getRatio();
    int w_w = (float)w_h * ((float)scene->getTDWidth() / (float)scene->getTDHeight());
    int h = w_h * ((float)getHeight() / 100.f);
    int d_h = scene->convertWorldCoordToWindow(worldHeight);

    if (coords != 0) {
        for (int i = 0; i < lastSize; i++) {
            delete coords[i];
        }

        delete coords;
    }

    lastSize = 4 + fractures.size();
    coords = new double*[lastSize];
    float _coords[lastSize * 2];
    lastSelected = 0;
    maxX = getLeft() * w_w + getRight() * w_w;
    minY = d_h - h;
    minX = getLeft() * w_w + getRight() * w_w;
    for (int i = 0; i < fractures.size() + 4; i++) {
        coords[i] = new double[2];

        if (i < fractures.size()) {
            Mover *m = fractures.at(i);
            coords[i][0] = m->getPosX() * scene->getRatio();
            coords[i][1] = scene->convertWorldCoordToWindow(m->getPosY());

            setBorders(coords[i][0], coords[i][1], height);
            _coords[i * 2] = (float)coords[i][0];
            _coords[i * 2 + 1] = (float)coords[i][1];

            if (m->isSelected())
                lastSelected = m;
        }
    }

    coords[lastSize - 4][0] = getLeft() * w_w + getRight() * w_w;
    coords[lastSize - 4][1] = d_h - h;

    coords[lastSize - 3][0] = getLeft() * w_w + getRight() * w_w;
    coords[lastSize - 3][1] = d_h;

    coords[lastSize - 2][0] = getLeft() * w_w;
    coords[lastSize - 2][1] = d_h;

    coords[lastSize - 1][0] = getLeft() * w_w;
    coords[lastSize - 1][1] = d_h - h;

    for (int i = lastSize - 4; i < lastSize; i++) {
        setBorders(coords[i][0], coords[i][1], height);
        _coords[i * 2] = (float)coords[i][0];
        _coords[i * 2 + 1] = (float)coords[i][1];
    }

    painter->beginNativePainting();

    if (tex != 0) {
        glDisable(GL_BLEND);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tex->id);
    }

    GLUtesselator *tobj = gluNewTess();
    gluTessProperty(tobj, GLU_TESS_WINDING_RULE, GLU_TESS_WINDING_ODD);
    gluTessProperty(tobj, GLU_TESS_BOUNDARY_ONLY, 0);
    gluTessProperty(tobj, GLU_TESS_TOLERANCE, 0);

    gluTessCallback(tobj, GLU_TESS_BEGIN, (_GLUfuncptr)glBegin);
    gluTessCallback(tobj, GLU_TESS_END, (_GLUfuncptr)glEnd);
    gluTessCallback(tobj, GLU_TESS_VERTEX, (_GLUfuncptr)tessVertex);

    glColor3f(1.0, 1.0, 1.0);
    gluTessBeginPolygon(tobj, NULL);
    {
        gluTessBeginContour(tobj);
        {
            for (int i = 0; i < lastSize; i++)
                gluTessVertex(tobj, coords[i], coords[i]);
        }
        gluTessEndContour(tobj);
    }
    gluTessEndPolygon(tobj);

    gluDeleteTess(tobj);

    glDisable(GL_TEXTURE_2D);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3f(0.0, 1.0, 0.0);

    glVertexPointer(2, GL_FLOAT, 0, _coords);
    glDrawArrays(GL_LINE_LOOP, 0, lastSize);

    glColor3f(1.0, 1.0, 1.0);
    glDisableClientState(GL_VERTEX_ARRAY);

    painter->endNativePainting();
}

void Landscape::paintFractures(QPainter *painter, QPaintEvent *event, Scene *scene)
{
    foreach (Mover *m, fractures)
        m->paint(painter, event, scene);
}

void Landscape::setTexX(int tX)
{
    PropertyManagers::getInstance()->getIntPropertyManager()->setValue(this->tX, tX);
}

void Landscape::setTexY(int tY)
{
    PropertyManagers::getInstance()->getIntPropertyManager()->setValue(this->tY, tY);
}

void Landscape::setLeft(int left)
{
    PropertyManagers::getInstance()->getIntPropertyManager()->setValue(this->left, left);
}

void Landscape::setRight(int right)
{
    PropertyManagers::getInstance()->getIntPropertyManager()->setValue(this->right, right);
}

void Landscape::setHeight(int height)
{
    lastHeight = height;
    PropertyManagers::getInstance()->getIntPropertyManager()->setValue(this->height, height);
}

Mover *Landscape::getMover(int w_x, int w_y)
{
    foreach (Mover *m, fractures) {
        if (m->check(w_x, w_y, scene)) {
            return m;
        }
    }

    return 0;
}

Mover *Landscape::addMover(int w_x, int w_y)
{
    Mover *m = new Mover(propertyBrowser);
    float r = scene->getRatio();
    m->setPosX((float)(w_x + scene->getSlide()) / r);
    m->setPosY(scene->convertWindowCoordToWorld(w_y));


    for (int i = fractures.size() - 1; i >= 0; i--) {
        if (fractures.at(i)->getPosX() <= m->getPosX()) {
            fractures.insert(i + 1, m);
            return m;
        }
    }

    if (fractures.size() == 0) {
        fractures << m;
    } else {
        fractures.insert(0, m);
    }
    return m;
}

void Landscape::save(QXmlStreamWriter *xml, bool toExport)
{
    xml->writeStartElement("landscape");
    {
        xml->writeAttribute("left", left->valueText());
        xml->writeAttribute("right", right->valueText());
        xml->writeAttribute("height", height->valueText());

        foreach (Mover *m, fractures) {
            xml->writeStartElement("fracture");
            {
                xml->writeAttribute("x", QString::number(m->getPosX()));
                xml->writeAttribute("y", QString::number(m->getPosY()));
            }
            xml->writeEndElement();
        }
    }
    xml->writeEndElement();
}

void Landscape::load(QXmlStreamReader *xml)
{
    fractures.clear();
    setLeft(xml->attributes().value("left").toString().toInt());
    setRight(xml->attributes().value("right").toString().toInt());
    setHeight(xml->attributes().value("height").toString().toInt());

    xml->readNext();
    while (!xml->atEnd()) {
        if (xml->isEndElement()) {
            xml->readNext();
            break;
        }

        if (xml->isStartElement()) {
            if (xml->name() == "fracture") {
                int x = xml->attributes().value("x").toString().toInt();
                int y = xml->attributes().value("y").toString().toInt();
                Mover *m = new Mover(propertyBrowser);
                m->setPosX(x);
                m->setPosY(y);
                fractures << m;

                xml->skipCurrentElement();
                xml->readNext();
            }
        } else {
            xml->readNext();
        }
    }
}

void Landscape::landscapeHeightChanged(QtProperty *property)
{
    if (property == height) {
        foreach (Mover *m, fractures) {
            float d = (float)(getHeight() - lastHeight) / 100.0;
            m->translate(0, (int)((float)worldHeight * d));
        }

        lastHeight = getHeight();
    }
}
