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
 36;
 -31.77427;0.00000;31.47596;,
 11.52983;0.00000;31.47596;,
 11.52983;0.00000;18.60328;,
 -31.77427;0.00000;18.60328;,
 26.05537;0.00000;28.05167;,
 29.81616;0.00000;12.36445;,
 33.47972;0.00000;24.32305;,
 40.36970;0.00000;17.36345;,
 -11.47469;0.00000;-5.21393;,
 11.52983;0.00000;-5.21393;,
 11.52983;0.00000;-13.54493;,
 -11.47469;0.00000;-13.54493;,
 29.73973;0.00000;-4.03700;,
 26.05537;0.00000;-11.97116;,
 43.78439;0.00000;1.40751;,
 41.83380;0.00000;-6.00154;,
 11.52983;0.00000;-21.87595;,
 -11.47469;0.00000;-21.87595;,
 26.05537;0.00000;-20.30217;,
 37.68004;0.00000;-14.33255;,
 -32.04672;0.00000;-13.54493;,
 -10.90509;0.00000;4.68433;,
 -10.90509;0.00000;-13.54493;,
 -32.04672;0.00000;-13.54493;,
 -10.90509;0.00000;-31.77418;,
 32.48923;0.00000;3.44837;,
 42.30507;0.00000;12.24897;,
 -0.40128;0.00000;-8.37396;,
 49.24885;0.00000;-8.37396;,
 49.24885;0.00000;9.44474;,
 -0.40128;0.00000;9.44474;,
 -49.25931;0.00000;0.71133;,
 0.39085;0.00000;-17.10739;,
 0.39085;0.00000;0.71133;,
 -49.25931;0.00000;0.71133;,
 0.39085;0.00000;18.53005;;
 
 16;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;8,9,10,11;,
 4;9,12,13,10;,
 4;12,14,15,13;,
 4;11,10,16,17;,
 4;10,13,18,16;,
 4;13,15,19,18;,
 3;20,21,22;,
 3;23,22,24;,
 4;25,5,7,26;,
 4;25,26,14,12;,
 4;27,28,29,30;,
 3;31,32,33;,
 3;34,33,35;;
 
 MeshMaterialList {
  1;
  16;
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
   0.388800;0.800000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  3;
  0.000000;1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  16;
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  3;0,1,0;,
  3;0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;2,2,2,2;,
  3;2,2,2;,
  3;2,2,2;;
 }
 MeshTextureCoords {
  36;
  0.400000;0.285710;,
  0.600000;0.285710;,
  0.600000;0.428570;,
  0.400000;0.428570;,
  0.800000;0.285710;,
  0.800000;0.428570;,
  1.000000;0.285710;,
  1.000000;0.428570;,
  0.400000;0.571430;,
  0.600000;0.571430;,
  0.600000;0.714290;,
  0.400000;0.714290;,
  0.800000;0.571430;,
  0.800000;0.714290;,
  1.000000;0.571430;,
  1.000000;0.714290;,
  0.600000;0.857140;,
  0.400000;0.857140;,
  0.800000;0.857140;,
  1.000000;0.857140;,
  0.000000;0.642860;,
  0.200000;0.571430;,
  0.200000;0.714290;,
  0.000000;0.785710;,
  0.200000;0.857140;,
  0.800000;0.500000;,
  1.000000;0.500000;,
  0.800000;0.285710;,
  1.000000;0.285710;,
  1.000000;0.428570;,
  0.800000;0.428570;,
  0.000000;0.357140;,
  0.200000;0.285710;,
  0.200000;0.428570;,
  0.000000;0.500000;,
  0.200000;0.571430;;
 }
}
