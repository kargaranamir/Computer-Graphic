#include <iostream> 
#include <vector> 
#include <stdio.h>
#include <glew.h>
#include <wglew.h>
#include <windows.h>
#include <mmsystem.h>
#include <GL/glut.h>
using namespace std;
#pragma comment(lib,"winmm.lib")
#include "Bmp.h"
#include "ogl.h"
#include "glsl.h"

vec4f lightvec(-1,0,-1,0);
#include "Mesh.h"

void DrawScene()
{
	if ( GetAsyncKeyState(VK_ESCAPE) )  exit(0);

	POINT cursor; // mouse
	GetCursorPos(&cursor); 
	float	viewangle_x = float(cursor.x-1280/2)/4.0;
	float	viewangle_y = float(cursor.y-768/2)/4.0;


	static uint t0=timeGetTime(); 
	double time_elapsed=double(timeGetTime()-t0)/1000;

	glClearDepth(1);
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// projection
	int vp[4];
	glMatrixMode( GL_PROJECTION);
	glLoadIdentity();
	glGetIntegerv(GL_VIEWPORT, vp);
	gluPerspective(90.0,float(vp[2])/float(vp[3]) , 0.01, 100);

	// modelview
	glMatrixMode( GL_MODELVIEW);
	glLoadIdentity();
	glRotatef( viewangle_y,1,0,0);		// set rotation
	glRotatef( viewangle_x,0,1,0);		// set rotation

	// select level of detail for rendering
	// (lods are generated automatically by the ogre xml converter )

	int lod=0; 
	if(GetAsyncKeyState(VK_F1)) lod=1;
	if(GetAsyncKeyState(VK_F2)) lod=2;
	if(GetAsyncKeyState(VK_F3)) lod=3;
	if(GetAsyncKeyState(VK_F4)) lod=4;
	if(GetAsyncKeyState(VK_F5)) lod=5;


	static Mesh halo   ("../data/halo/halo.material",		//	required material file
						"../data/halo/halo.mesh.xml",		//	required mesh file
						"../data/halo/halo.skeleton.xml");	//	optional skeleton file
	for (int i = 0; i < 4; ++i)
	{ 
		// Set the skeleton to an animation at a given time
		halo.animation.SetPose(
			i/2,			
			time_elapsed );

		// F6 
		if(GetAsyncKeyState(VK_F6))
		{
			// get the index
			int index  = halo.animation.GetBoneIndexOf("joint2"); 

			// get / modify / set the matrix
			matrix44 m = halo.animation.bones[ index ].matrix;
			m.x_component()=vec3f(1,0,0);
			m.y_component()=vec3f(0,1,0); // set the rotation to identity
			m.z_component()=vec3f(0,0,1);
			halo.animation.bones[ index ].matrix=m;

			// re-evaluate the childs
			loopi(0,halo.animation.bones[ index ].childs.size())
			{
				halo.animation.EvalSubtree(
					halo.animation.bones[ index ].childs[i],	// bone id
					halo.animation.animations[0],				// animation
					-1);										// key frame -1 means not use the animation
			}
		}
		
		// Draw the model
		halo.Draw(
			vec3f((i-1.5)*7,-5,7),			// position
			vec3f(0,time_elapsed*0.3,0),	// rotation
			lod,							// LOD level
			(i&1)==1 );						// draw skeleton ?
	}
	
	// Swap
	glutSwapBuffers();
	
}



///////////////////////////////////////////
int main(int argc, char **argv) 
{ 
  glutInit(&argc, argv);  
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  
  glutInitWindowSize(1280, 768);  
  glutInitWindowPosition(0, 0);  
  glutCreateWindow("Skeletal Animation");
  glutDisplayFunc(DrawScene);
  glutIdleFunc(DrawScene);
  glewInit();
  wglSwapIntervalEXT(0);
  glutMainLoop();  
  return 0;
}
///////////////////////////////////////////
