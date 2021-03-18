
#include "Metaball.h"

CubeVertices::CubeVertices(int blocks)
{
	n_blocks = blocks;
	if (blocks > max_blocks)
		n_blocks = 200;




	n_cubes = n_blocks * n_blocks * n_blocks;

	vertices = new Vertix[(n_blocks + 1) * (n_blocks + 1) * (n_blocks + 1)];
	cubes = new Cube[n_blocks * n_blocks * n_blocks];

	int cur = 0;

	for (int i = 0; i < n_blocks + 1; i++)
	{
		for (int j = 0; j < n_blocks + 1; j++)
		{
			for (int k = 0; k < n_blocks + 1; k++)
			{
				vertices[cur].position = Vec3f((i * 20.0f) / (n_blocks)- 10.0, 
					(j * 20.0f) / (n_blocks)- 10.0, 
					(k * 20.0f) / (n_blocks)- 10.0);
				vertices[cur].value = 0.0f;
				cur++;
			}
		}
	}

	cur = 0;

	for (int i = 0; i < n_blocks; i++)
	{
		for (int j = 0; j < n_blocks; j++)
		{
			for (int k = 0; k < n_blocks; k++)
			{
				cubes[cur].vertices[0] = &vertices[k + j * (n_blocks + 1) + i * (n_blocks + 1) * (n_blocks + 1)];
				cubes[cur].vertices[1] = &vertices[(k + 1) + j * (n_blocks + 1) + i * (n_blocks + 1) * (n_blocks + 1)];
				cubes[cur].vertices[2] = &vertices[(k + 1) + (j + 1) * (n_blocks + 1) + i * (n_blocks + 1) * (n_blocks + 1)];
				cubes[cur].vertices[3] = &vertices[k + (j + 1) * (n_blocks + 1) + i * (n_blocks + 1) * (n_blocks + 1)];
				cubes[cur].vertices[4] = &vertices[k + j * (n_blocks + 1) + (i + 1) * (n_blocks + 1) * (n_blocks + 1)];
				cubes[cur].vertices[5] = &vertices[(k + 1) + j * (n_blocks + 1) + (i + 1) * (n_blocks + 1) * (n_blocks + 1)];
				cubes[cur].vertices[6] = &vertices[(k + 1) + (j + 1) * (n_blocks + 1) + (i + 1) * (n_blocks + 1) * (n_blocks + 1)];
				cubes[cur].vertices[7] = &vertices[k + (j + 1) * (n_blocks + 1) + (i + 1) * (n_blocks + 1) * (n_blocks + 1)];
				cur++;
			}
		}
	}

	n_metaball++;
	metaball[n_metaball - 1].position =Vec3f(0.0,0.0,0.0);
	metaball[n_metaball - 1].radius = 1.5f;

	n_metaball++;
	metaball[n_metaball - 1].position = Vec3f(0.0, 0.0, 0.0);
	metaball[n_metaball - 1].radius = 1.5f;

}



void CubeVertices::Update()
{
	for (int i = 0; i < (n_blocks + 1) * (n_blocks + 1) * (n_blocks + 1); i++)
	{
		vertices[i].value = 0.0;
	}

	for(int j=0; j<n_metaball;j++)
	{
		for (int i = 0; i < (n_blocks + 1) * (n_blocks + 1) * (n_blocks + 1); i++)
		{


			Vec3f delta = metaball[j].position - vertices[i].position;
			float square_distance = delta.length2();
			if(square_distance< 0.0001f)
				square_distance = 0.0001f;
			vertices[i].value += pow(metaball[j].radius, 2.0) / delta.length2();
		}
	}

}

void CubeVertices::drawSurface()
{
	setDiffuseColor(0.8, 0.8, 0);
	//drawSphere(1);

	glBegin(GL_TRIANGLES);


	for (int i = 0; i < n_cubes; i++)
	{
		int type = 0;
		if(cubes[i].vertices[0]->value>=1)
			type += 1;
		if (cubes[i].vertices[1]->value >= 1)
			type += 2;
		if (cubes[i].vertices[2]->value >= 1)
			type += 4;
		if (cubes[i].vertices[3]->value >= 1)
			type += 8;
		if (cubes[i].vertices[4]->value >= 1)
			type += 16;
		if (cubes[i].vertices[5]->value >= 1)
			type += 32;
		if (cubes[i].vertices[6]->value >= 1)
			type += 64;
		if (cubes[i].vertices[7]->value >= 1)
			type += 128;


		if (type == 0 || type==255)
			continue;

		for (int j = 0; CubeTable[type][j] != -1; j += 3)
		{
			glVertex3f(edges[CubeTable[type][j]][0]* 20.0f/ (n_blocks)+ cubes[i].vertices[0]->position[0],
					edges[CubeTable[type][j]][1] * 20.0f / (n_blocks)+ cubes[i].vertices[0]->position[1],
					edges[CubeTable[type][j]][2]* 20.0f / (n_blocks)+ cubes[i].vertices[0]->position[2]);


			glVertex3f(edges[CubeTable[type][j+1]][0]* 20.0f / (n_blocks)+ cubes[i].vertices[0]->position[0],
				edges[CubeTable[type][j+1]][1]* 20.0f / (n_blocks)+ cubes[i].vertices[0]->position[1],
				edges[CubeTable[type][j+1]][2]* 20.0f / (n_blocks)+ cubes[i].vertices[0]->position[2]);
			glVertex3f(edges[CubeTable[type][j+2]][0]* 20.0f / (n_blocks)+ cubes[i].vertices[0]->position[0],
				edges[CubeTable[type][j+2]][1]* 20.0f / (n_blocks)+ cubes[i].vertices[0]->position[1],
				edges[CubeTable[type][j+2]][2]* 20.0f / (n_blocks)+ cubes[i].vertices[0]->position[2]);
		}

	}

	glEnd();
}