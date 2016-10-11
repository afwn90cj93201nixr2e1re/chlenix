#pragma once

#include "main.h"

class cFont
{
public:

	DWORD dwFontId;

	cFont()
	{
		dwFontId = 0;
	}

	void SetFont( char* name , int h , int w , int flag );
	void DrawString( int x , int y , Color color , bool center , char* string );
};

class cDrawing
{
public:

	void DrawLine( Vector vStart , Vector vEnd , Color color );
	void OutlinedRect( int x , int y , int w , int h , Color color );
	void FillArea( int x , int y , int w , int h , Color color );
	void DrawBox( int x , int y , int w , int h , Color color );
	void DrawOutlineBox( int x , int y , int w , int h , Color color , bool inBox );
	void DrawCoalBox( int x , int y , int w , int h , Color color );
	void DrawOutlineCoalBox( int x , int y , int w , int h , Color color , bool inBox );
	void DrawHorBar( int x , int y , int w , int h , int val , Color color1 , Color color2 );
	void DrawVerBar( int x , int y , int w , int h , int val , Color color1 , Color color2 );
};

extern cFont g_FontEsp;
extern cFont g_FontMenu;
extern cDrawing g_Draw;