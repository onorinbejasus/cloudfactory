/*
 *  MetaballCanvas.cpp
 *  CloudFactory
 *
 *  Created by Victor Powell on 4/10/11.
 *  Copyright 2011 University of Pittsburgh. All rights reserved.
 *
 */

#include "MetaballCanvas.h"

MetaballCanvas::MetaballCanvas(){
	
	//init
	SX = 200;
	SY = 200;
	SZ = 50;
	MAX_INDICES = 1024;
	ball1 = 0;
	ball2 = 0;
	t = 0;
	
	metaballs = newFloatMatrix(SX,SY,SZ);
	
    
	//int stride = vformat->GetStride();
	
	//vbuffer = new0 VertexBuffer(MAX_INDICES, stride);
	//ibuffer = new0 IndexBuffer(MAX_INDICES, 4);
	
	myMesh = NULL;
	cout << "MetaballCanvas mesh: " << myMesh << endl;
	//TriMesh* mesh = new0 TriMesh(vformat, vbuffer, ibuffer);

}






void MetaballCanvas::draw(){
	
	//for metaballs
	t=5;
	ball1 = sin(t/10.0) * 50 + 100 ;
	ball2 = SX - ball1;
	
	initVoxels(metaballs,SX,SY,SZ);
	drawMetaball(metaballs,SX,SY,SZ,ball1,SY/2,SZ-5,10);
	drawMetaball(metaballs,SX,SY,SZ,ball2,SY/2,SZ-5,10);
	
	drawMetaball(metaballs,SX,SY,SZ,SX/2,ball1,SZ-5,10);
	drawMetaball(metaballs,SX,SY,SZ,SX/2,ball2,SZ-5,10);
	
	clearVertexList();
	vertices = runMarchingCubes(metaballs,SX,SY,SZ,6,6,6,1);
	
	if(myMesh!=NULL){
		this->DetachChildAt(0);
		cout << "myMesh: " << myMesh << endl;
		//delete myMesh;
	}
	myMesh = regenerate_metaballs_mesh(vertices);
	myMesh->LocalTransform.SetScale(APoint(1.0 / SX, 1.0 / SX , 1.0 / SX ));
	myMesh->LocalTransform.SetRotate(HMatrix(AVector::UNIT_Y, Mathf::DEG_TO_RAD * 180 ));
	this->SetChild(0,myMesh);
	this->Update();

}















//void MetaballCanvas::updateTriMesh( VertexFormat* format, VertexBuffer* vbuffer, IndexBuffer* ibuffer, list<vertex>& vertices, int max_indices )
//{
//    int numVertices = (vertices.size()<max_indices)?vertices.size():max_indices;
//    int numTriangles = numVertices/3;
//    int numIndices = numVertices;
//    int stride = format->GetStride();
//	bool mHasNormals = false;
//	bool mHasTCoords[VertexFormat::AM_MAX_TCOORD_UNITS];  
//		
//	vbuffer->SetNumElements(numVertices);
//	ibuffer->SetNumElements(numIndices);
//	
//	//textures depends on this. i pull this code out of Wm5StandardMesh.[cpp,h]
//	for (int unit = 0; unit < VertexFormat::AU_TEXCOORD; ++unit)
//    {
//        mHasTCoords[unit] = false;
//        int tcdIndex = format->GetIndex(VertexFormat::AU_TEXCOORD, unit);
//        if (tcdIndex >= 0)
//        {
//            VertexFormat::AttributeType tcdType = format->GetAttributeType(tcdIndex);
//			
//            if (tcdType == VertexFormat::AT_FLOAT2)
//            {
//                mHasTCoords[unit] = true;
//            }
//        }
//    }
//	
//	
//	//normals depends on this. i pull this code out of Wm5StandardMesh.[cpp,h]
//	int norIndex = format->GetIndex(VertexFormat::AU_NORMAL);
//    if (norIndex >= 0)
//    {
//        VertexFormat::AttributeType norType =
//		format->GetAttributeType(norIndex);
//		
//        if (norType == VertexFormat::AT_FLOAT3)
//        {
//            mHasNormals = true;
//        }
//    }
//	
//	
//    VertexBufferAccessor vba(format, vbuffer);
//	
//    // Generate geometry.
//	list<vertex>::iterator it;
//	int i = 0;
//	for(it = vertices.begin(); it != vertices.end(); it++) {
//		//it->normal_x, it->normal_y, it->normal_z
//		vba.Position<Float3>(i++) = Float3(it->x,it->y,it->z);
//	}
//	
//	// I'm not gonna worry about textures for now..
//	
//	//	for (int unit = 0; unit < VertexFormat::AU_TEXCOORD; ++unit)
//	//    {
//	//        if (mHasTCoords[unit])
//	//        {
//	//            vba.TCoord<Float2>(unit, 0) = Float2(0.25f, 0.75f);
//	//            vba.TCoord<Float2>(unit, 1) = Float2(0.75f, 0.75f);
//	//            vba.TCoord<Float2>(unit, 2) = Float2(0.75f, 0.25f);
//	//        }
//	//    }
//	
//	
//    // Generate indices (outside view).
//	
//    int* indices = (int*)ibuffer->GetData();
//    for(int i = 0; i < numIndices; i++)
//		indices[i] = i;
//	
//    myMesh = new0 TriMesh(format, vbuffer, ibuffer);
//    if (mHasNormals)
//    {
//        myMesh->UpdateModelSpace(Visual::GU_NORMALS);
//    }
//	
//}




TriMesh* MetaballCanvas::getTriMeshFromVertexList(list<vertex>& vertices )
{
	
	//init TriMesh
	VertexFormat* format = VertexFormat::Create(3,
								   VertexFormat::AU_POSITION, VertexFormat::AT_FLOAT3, 0,
								   VertexFormat::AU_NORMAL, VertexFormat::AT_FLOAT3, 0,
								   VertexFormat::AU_TEXCOORD, VertexFormat::AT_FLOAT2, 0);	
	
    int numVertices = vertices.size();
    int numTriangles = vertices.size()/3;
    int numIndices = numVertices;
    int stride = format->GetStride();
	bool mHasNormals = false;
	bool mHasTCoords[VertexFormat::AM_MAX_TCOORD_UNITS];
	
	//textures depends on this. i pull this code out of Wm5StandardMesh.[cpp,h]
	for (int unit = 0; unit < VertexFormat::AU_TEXCOORD; ++unit)
    {
        mHasTCoords[unit] = false;
        int tcdIndex = format->GetIndex(VertexFormat::AU_TEXCOORD, unit);
        if (tcdIndex >= 0)
        {
            VertexFormat::AttributeType tcdType = format->GetAttributeType(tcdIndex);
			
            if (tcdType == VertexFormat::AT_FLOAT2)
            {
                mHasTCoords[unit] = true;
            }
        }
    }
	
	
	//normals depends on this. i pull this code out of Wm5StandardMesh.[cpp,h]
	int norIndex = format->GetIndex(VertexFormat::AU_NORMAL);
    if (norIndex >= 0)
    {
        VertexFormat::AttributeType norType =
		format->GetAttributeType(norIndex);
		
        if (norType == VertexFormat::AT_FLOAT3)
        {
            mHasNormals = true;
        }
    }
	
	
    // Create a vertex buffer.
    VertexBuffer* vbuffer = new0 VertexBuffer(numVertices, stride);
    VertexBufferAccessor vba(format, vbuffer);
	
    // Generate geometry.
	list<vertex>::iterator it;
	int i = 0;
	for(it = vertices.begin(); it != vertices.end(); it++) {
		//it->normal_x, it->normal_y, it->normal_z
		vba.Position<Float3>(i++) = Float3(it->x,it->y,it->z);
	}
	
	// I'm not gonna worry about textures for now..
	
//	for (int unit = 0; unit < VertexFormat::AU_TEXCOORD; ++unit)
//    {
//        if (mHasTCoords[unit])
//        {
//            vba.TCoord<Float2>(unit, 0) = Float2(0.25f, 0.75f);
//            vba.TCoord<Float2>(unit, 1) = Float2(0.75f, 0.75f);
//            vba.TCoord<Float2>(unit, 2) = Float2(0.75f, 0.25f);
//        }
//    }
	
	
    // Generate indices (outside view).
    IndexBuffer* ibuffer = new0 IndexBuffer(numIndices, 4);
    int* indices = (int*)ibuffer->GetData();
    for(int i = 0; i < numIndices; i++)
		indices[i] = i;
	
    TriMesh* mesh = new0 TriMesh(format, vbuffer, ibuffer);
    if (mHasNormals)
    {
        mesh->UpdateModelSpace(Visual::GU_NORMALS);
    }
    return mesh;
}










TriMesh *MetaballCanvas::regenerate_metaballs_mesh(list<vertex>& vertices)
{
	
	myMesh = getTriMeshFromVertexList(vertices);
	std::string baseName = Environment::GetPathR("My_Brick.wmtf");
    Texture2D* baseTexture = Texture2D::LoadWMTF(baseName);
	myMesh->SetEffectInstance(Texture2DEffect::CreateUniqueInstance(baseTexture, Shader::SF_LINEAR,Shader::SC_CLAMP_EDGE, Shader::SC_CLAMP_EDGE));
	return myMesh;
}