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
 -0.00078;-20.93172;-4.76261;,
 3.23556;-20.93172;-3.36750;,
 -0.00078;-20.93172;0.00057;,
 4.57608;-20.93172;0.00057;,
 -0.00078;-20.93172;0.00057;,
 3.23556;-20.93172;3.36864;,
 -0.00078;-20.93172;0.00057;,
 -0.00080;-20.93172;4.76376;,
 -0.00078;-20.93172;0.00057;,
 -3.23712;-20.93172;3.36864;,
 -0.00078;-20.93172;0.00057;,
 -4.57767;-20.93172;0.00057;,
 -0.00078;-20.93172;0.00057;,
 -3.23712;-20.93172;-3.36750;,
 -0.00078;-20.93172;0.00057;,
 -0.00078;-20.93172;-4.76261;,
 -0.00078;-20.93172;0.00057;,
 3.48711;-0.00066;-3.62915;,
 -0.00065;-0.00066;-5.13263;,
 -0.00065;-0.00066;0.00057;,
 4.93175;-0.00066;0.00057;,
 -0.00065;-0.00066;0.00057;,
 3.48711;-0.00066;3.63029;,
 -0.00065;-0.00066;0.00057;,
 -0.00066;-0.00066;5.13377;,
 -0.00065;-0.00066;0.00057;,
 -3.48839;-0.00066;3.63029;,
 -0.00065;-0.00066;0.00057;,
 -4.93308;-0.00066;0.00057;,
 -0.00065;-0.00066;0.00057;,
 -3.48839;-0.00066;-3.62915;,
 -0.00065;-0.00066;0.00057;,
 -0.00065;-0.00066;-5.13263;,
 -0.00065;-0.00066;0.00057;,
 3.82328;-4.20786;-4.12607;,
 -0.10799;-4.20786;-5.82072;,
 -3.93189;-4.25952;-4.09070;,
 -0.10799;-4.20786;-5.82072;,
 5.55896;-4.25952;0.00057;,
 -5.56029;-4.25952;0.00057;,
 3.93060;-4.25952;4.09185;,
 -3.93189;-4.25952;4.09185;,
 -0.00066;-4.25952;5.78651;,
 -3.93201;-16.35021;-4.09070;,
 -0.10809;-16.29855;-5.82072;,
 3.82316;-16.29855;-4.12607;,
 -0.10809;-16.29855;-5.82072;,
 -5.56040;-16.35021;0.00057;,
 5.55884;-16.35021;0.00057;,
 -3.93201;-16.35021;4.09185;,
 3.93048;-16.35021;4.09185;,
 -0.00077;-16.35021;5.78651;;
 
 40;
 3;0,1,2;,
 3;1,3,4;,
 3;3,5,6;,
 3;5,7,8;,
 3;7,9,10;,
 3;9,11,12;,
 3;11,13,14;,
 3;13,15,16;,
 3;17,18,19;,
 3;20,17,21;,
 3;22,20,23;,
 3;24,22,25;,
 3;26,24,27;,
 3;28,26,29;,
 3;30,28,31;,
 3;32,30,33;,
 4;18,17,34,35;,
 4;36,30,32,37;,
 4;17,20,38,34;,
 4;39,28,30,36;,
 4;20,22,40,38;,
 4;41,26,28,39;,
 4;22,24,42,40;,
 4;42,24,26,41;,
 4;43,36,37,44;,
 4;15,13,43,44;,
 4;45,1,0,46;,
 4;35,34,45,46;,
 4;47,39,36,43;,
 4;13,11,47,43;,
 4;48,3,1,45;,
 4;34,38,48,45;,
 4;49,41,39,47;,
 4;11,9,49,47;,
 4;50,5,3,48;,
 4;38,40,50,48;,
 4;51,42,41,49;,
 4;9,7,51,49;,
 4;51,7,5,50;,
 4;40,42,51,50;;
 
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
   0.276000;0.276000;0.276000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  34;
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  -0.006739;0.078825;-0.996866;,
  0.710316;0.071836;-0.700207;,
  -0.719819;0.077035;-0.689874;,
  0.997451;0.070988;-0.007193;,
  -0.997324;0.073103;-0.000000;,
  0.715056;0.074536;0.695082;,
  -0.715053;0.074543;0.695085;,
  -0.000001;0.076037;0.997105;,
  -0.006116;-0.110609;-0.993845;,
  -0.717314;-0.109028;-0.688166;,
  0.708029;-0.103784;-0.698515;,
  -0.994408;-0.105607;-0.000000;,
  0.994598;-0.103520;-0.007676;,
  -0.712921;-0.107662;0.692930;,
  0.712923;-0.107672;0.692927;,
  -0.000001;-0.109801;0.993953;,
  -0.004513;0.156869;-0.987609;,
  0.706720;0.143353;-0.692818;,
  -0.712152;0.153603;-0.685015;,
  0.989944;0.141381;-0.004682;,
  -0.989329;0.145701;-0.000000;,
  0.709134;0.148545;0.689249;,
  -0.709131;0.148545;0.689251;,
  -0.000002;0.151498;0.988458;,
  -0.003243;-0.219201;-0.975674;,
  -0.702889;-0.216626;-0.677510;,
  0.698194;-0.206310;-0.685537;,
  -0.977760;-0.209729;-0.000000;,
  0.978654;-0.205438;-0.005602;,
  -0.700599;-0.213726;0.680795;,
  0.700600;-0.213731;0.680792;,
  -0.000001;-0.217873;0.975977;;
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
  4;18,19,3,2;,
  4;4,20,18,2;,
  4;19,21,5,3;,
  4;6,22,20,4;,
  4;21,23,7,5;,
  4;8,24,22,6;,
  4;23,25,9,7;,
  4;9,25,24,8;,
  4;11,4,2,10;,
  4;26,27,11,10;,
  4;12,28,26,10;,
  4;2,3,12,10;,
  4;13,6,4,11;,
  4;27,29,13,11;,
  4;14,30,28,12;,
  4;3,5,14,12;,
  4;15,8,6,13;,
  4;29,31,15,13;,
  4;16,32,30,14;,
  4;5,7,16,14;,
  4;17,9,8,15;,
  4;31,33,17,15;,
  4;17,33,32,16;,
  4;7,9,17,16;;
 }
 MeshTextureCoords {
  52;
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.062500;0.000000;,
  0.250000;0.000000;,
  0.187500;0.000000;,
  0.375000;0.000000;,
  0.312500;0.000000;,
  0.500000;0.000000;,
  0.437500;0.000000;,
  0.625000;0.000000;,
  0.562500;0.000000;,
  0.750000;0.000000;,
  0.687500;0.000000;,
  0.875000;0.000000;,
  0.812500;0.000000;,
  1.000000;0.000000;,
  0.937500;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.062500;1.000000;,
  0.250000;1.000000;,
  0.187500;1.000000;,
  0.375000;1.000000;,
  0.312500;1.000000;,
  0.500000;1.000000;,
  0.437500;1.000000;,
  0.625000;1.000000;,
  0.562500;1.000000;,
  0.750000;1.000000;,
  0.687500;1.000000;,
  0.875000;1.000000;,
  0.812500;1.000000;,
  1.000000;1.000000;,
  0.937500;1.000000;,
  0.125000;0.965230;,
  0.000000;0.965230;,
  0.875000;0.965230;,
  1.000000;0.965230;,
  0.250000;0.965230;,
  0.750000;0.965230;,
  0.375000;0.965230;,
  0.625000;0.965230;,
  0.500000;0.965230;,
  0.875000;0.127220;,
  1.000000;0.127220;,
  0.125000;0.127220;,
  0.000000;0.127220;,
  0.750000;0.127220;,
  0.250000;0.127220;,
  0.625000;0.127220;,
  0.375000;0.127220;,
  0.500000;0.127220;;
 }
}