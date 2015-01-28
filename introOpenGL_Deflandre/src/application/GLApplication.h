#ifndef GLAPPLICATION_H
#define GLAPPLICATION_H


#include "GLWidget.h"
#include "Tools.h"

#include <string>

class GLApplication : public GLWidget {
  Q_OBJECT  
public:
  GLApplication();
  virtual ~GLApplication();

  /** ***** **/
  /** GLApplication must implement these methods : */
  virtual void initialize();
  virtual void update();
  virtual void draw();
  virtual void resize(int width,int height);
  /** ***** **/
  virtual void leftPanel(int i, const std::string &s);
  virtual QSize sizeHint() const {return QSize(1000,1000);}
  /** ***** **/
  GLuint initProgram(const std::string &filename);
  void initTriangleBuffer();
  void initTriangleVAO();
  void initTexture();

private:
  std::vector<float> _trianglePosition;
  std::vector<float> _triangleColor;
  std::vector<float> _triangleTexCoord;
  std::vector<unsigned int> _elementData;

  GLuint _trianglePositionBuffer;
  GLuint _triangleColorBuffer;
  GLuint _triangleTexCoordBuffer;
  GLuint _elementBuffer;

  GLuint _triangleVAO;
  GLuint _shader0;
  GLuint _textureId;

  unsigned _vertices_number;
  float _coeff;
  float _coeff_step;

  /**
   * @brief initStrip
   * Initialise les positions et couleurs des triangles afin d'obtenir
   * un rectangle de \a nbSlice tranches.
   *
   * @param nbSlice
   * @param xmin
   * @param xmax
   * @param ymin
   * @param ymax
   */
  void initStrip(unsigned nbSlice,float xmin,float xmax,float ymin,float ymax);

  /**
   * @brief initRing
   * Initialise les positions et couleurs des triangles afin d'obtenir
   * un disque de \a nbSlice tranches.
   *
   * @param nbSlice
   * @param r0 rayon intérieur
   * @param r1 rayon extérieur
   */
  void initRing(unsigned nbSlice,float r0,float r1);

};

#endif // GLAPPLICATION_H

