#include "Texture.h"

#define MAX_VERTICES 10000
#define MAX_FACES    5000
#define MAX_NORMS    5000
#define MAX_PETALS   32

typedef struct mesh {
	float vertices[MAX_VERTICES][3];
	int vertex_count;
	int faces[MAX_FACES][4];
	int face_count;
	float normals[MAX_NORMS][3];
} mesh;


class lotusObject {
	public:
		lotusObject(int base_numb, int petal_layers, int x_segments, int y_segments);
        int petal_count = 0;
        mesh lotus[MAX_PETALS];
        int m_x_segments;
        int m_y_segments;
	
	private:

        Texture *gradtex;
        Texture *veintex;
        GLuint texPetal[2];
        GLvoid CalculateVectorNormal(int indx_lotus, int indx_face);
        void meshDuplicate(int indx_old, int indx_new);
        void doZRotation(int indx, float angle);
        void doYRotation(int indx, float angle);
        void ellipticalConnect(int indx, float a, float v1_x, float v1_y, float v2_x,float v2_y, int segments);
        void createPetalVertices(int indx, float a, float b,float c,float d, int x_seg, int y_seg, float start, float end);
        mesh makePetal(int indx, int x_seg, int y_seg);
        void createLotus(int base_numb, int petal_layers, int x_segments, int y_segments);

};