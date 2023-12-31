xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 52;
 -0.00047;0.00046;0.00000;,
 -0.00047;-1.30327;-1.65638;,
 -0.00047;0.00046;-2.34248;,
 -0.00047;0.00046;0.00000;,
 -0.00047;-1.84330;0.00000;,
 -0.00047;0.00046;0.00000;,
 -0.00047;-1.30327;1.65638;,
 -0.00047;0.00046;0.00000;,
 -0.00047;0.00046;2.34248;,
 -0.00047;0.00046;0.00000;,
 -0.00047;1.30420;1.65638;,
 -0.00047;0.00046;0.00000;,
 -0.00047;1.84422;0.00000;,
 -0.00047;0.00046;0.00000;,
 -0.00047;1.30420;-1.65638;,
 -0.00047;0.00046;0.00000;,
 -0.00047;0.00046;-2.34248;,
 -15.66588;0.00046;0.00000;,
 -15.66588;0.00046;-2.37779;,
 -15.66588;-1.32292;-1.68135;,
 -15.66588;0.00046;0.00000;,
 -15.66588;-1.87109;0.00000;,
 -15.66588;0.00046;0.00000;,
 -15.66588;-1.32292;1.68135;,
 -15.66588;0.00046;0.00000;,
 -15.66588;0.00046;2.37779;,
 -15.66588;0.00046;0.00000;,
 -15.66588;1.32385;1.68135;,
 -15.66588;0.00046;0.00000;,
 -15.66588;1.87202;0.00000;,
 -15.66588;0.00046;0.00000;,
 -15.66588;1.32385;-1.68135;,
 -15.66588;0.00046;0.00000;,
 -15.66588;0.00046;-2.37779;,
 -1.82506;1.74157;-2.21204;,
 -1.82506;0.00046;-3.12829;,
 -1.82506;2.46273;0.00000;,
 -1.82506;0.00046;-3.12829;,
 -1.82506;-1.74062;-2.21204;,
 -1.82506;1.74157;2.21204;,
 -1.82506;-2.46181;0.00000;,
 -1.82506;0.00046;3.12829;,
 -1.82506;-1.74062;2.21204;,
 -14.04194;1.74157;-2.21204;,
 -14.04194;0.00046;-3.12829;,
 -14.04194;2.46273;0.00000;,
 -14.04194;0.00046;-3.12829;,
 -14.04194;-1.74062;-2.21204;,
 -14.04194;1.74157;2.21204;,
 -14.04194;-2.46181;0.00000;,
 -14.04194;0.00046;3.12829;,
 -14.04194;-1.74062;2.21204;;
 
 40;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 3;17,18,19;,
 3;20,19,21;,
 3;22,21,23;,
 3;24,23,25;,
 3;26,25,27;,
 3;28,27,29;,
 3;30,29,31;,
 3;32,31,33;,
 4;34,14,16,35;,
 4;34,36,12,14;,
 4;37,2,1,38;,
 4;36,39,10,12;,
 4;38,1,4,40;,
 4;39,41,8,10;,
 4;40,4,6,42;,
 4;41,42,6,8;,
 4;43,34,35,44;,
 4;43,44,33,31;,
 4;43,31,29,45;,
 4;43,45,36,34;,
 4;46,37,38,47;,
 4;46,47,19,18;,
 4;45,29,27,48;,
 4;45,48,39,36;,
 4;47,38,40,49;,
 4;47,49,21,19;,
 4;48,27,25,50;,
 4;48,50,41,39;,
 4;49,40,42,51;,
 4;49,51,23,21;,
 4;50,25,23,51;,
 4;50,51,42,41;;
 
 MeshMaterialList {
  1;
  40;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.724800;0.564800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  34;
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.181051;0.752867;-0.632780;,
  0.203680;-0.000003;-0.979037;,
  0.163095;0.986610;0.000000;,
  0.181049;-0.752866;-0.632782;,
  0.181051;0.752867;0.632780;,
  0.163093;-0.986611;-0.000000;,
  0.203680;-0.000003;0.979037;,
  0.181049;-0.752866;0.632782;,
  -0.192986;0.751274;-0.631145;,
  -0.216859;-0.000003;-0.976203;,
  -0.174047;0.984737;0.000000;,
  -0.192984;-0.751273;-0.631147;,
  -0.192986;0.751274;0.631145;,
  -0.174046;-0.984738;0.000000;,
  -0.216859;-0.000003;0.976203;,
  -0.192984;-0.751273;0.631147;,
  0.354637;0.716918;-0.600217;,
  0.395555;-0.000003;-0.918442;,
  0.321046;0.947064;0.000000;,
  0.354633;-0.716918;-0.600220;,
  0.354637;0.716918;0.600217;,
  0.321042;-0.947065;-0.000000;,
  0.395555;-0.000003;0.918442;,
  0.354633;-0.716918;0.600220;,
  -0.419516;-0.000003;-0.907748;,
  -0.376943;0.710489;-0.594239;,
  -0.341846;0.939756;0.000000;,
  -0.376939;-0.710490;-0.594240;,
  -0.376943;0.710489;0.594239;,
  -0.341844;-0.939757;0.000000;,
  -0.419516;-0.000003;0.907748;,
  -0.376939;-0.710490;0.594240;;
  40;
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  4;2,18,19,3;,
  4;2,4,20,18;,
  4;3,19,21,5;,
  4;4,6,22,20;,
  4;5,21,23,7;,
  4;6,8,24,22;,
  4;7,23,25,9;,
  4;8,9,25,24;,
  4;10,2,3,11;,
  4;10,11,26,27;,
  4;10,27,28,12;,
  4;10,12,4,2;,
  4;11,3,5,13;,
  4;11,13,29,26;,
  4;12,28,30,14;,
  4;12,14,6,4;,
  4;13,5,7,15;,
  4;13,15,31,29;,
  4;14,30,32,16;,
  4;14,16,8,6;,
  4;15,7,9,17;,
  4;15,17,33,31;,
  4;16,32,33,17;,
  4;16,17,9,8;;
 }
 MeshTextureCoords {
  52;
  0.062500;0.000000;,
  0.125000;0.000000;,
  0.000000;0.000000;,
  0.187500;0.000000;,
  0.250000;0.000000;,
  0.312500;0.000000;,
  0.375000;0.000000;,
  0.437500;0.000000;,
  0.500000;0.000000;,
  0.562500;0.000000;,
  0.625000;0.000000;,
  0.687500;0.000000;,
  0.750000;0.000000;,
  0.812500;0.000000;,
  0.875000;0.000000;,
  0.937500;0.000000;,
  1.000000;0.000000;,
  0.062500;1.000000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.187500;1.000000;,
  0.250000;1.000000;,
  0.312500;1.000000;,
  0.375000;1.000000;,
  0.437500;1.000000;,
  0.500000;1.000000;,
  0.562500;1.000000;,
  0.625000;1.000000;,
  0.687500;1.000000;,
  0.750000;1.000000;,
  0.812500;1.000000;,
  0.875000;1.000000;,
  0.937500;1.000000;,
  1.000000;1.000000;,
  0.875000;0.103110;,
  1.000000;0.103110;,
  0.750000;0.103110;,
  0.000000;0.103110;,
  0.125000;0.103110;,
  0.625000;0.103110;,
  0.250000;0.103110;,
  0.500000;0.103110;,
  0.375000;0.103110;,
  0.875000;0.942250;,
  1.000000;0.942250;,
  0.750000;0.942250;,
  0.000000;0.942250;,
  0.125000;0.942250;,
  0.625000;0.942250;,
  0.250000;0.942250;,
  0.500000;0.942250;,
  0.375000;0.942250;;
 }
}
