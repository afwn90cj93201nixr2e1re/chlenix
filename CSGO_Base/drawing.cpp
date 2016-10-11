#include "main.h"
#include <comutil.h>

#pragma comment(lib, "comsuppw.lib")

cFont g_FontEsp;
cFont g_FontMenu;
cDrawing g_Draw;

void cFont::SetFont( char* name , int h , int w , int flag )
{
	if ( !dwFontId )
		dwFontId = g_pSurface->FontCreate();

	g_pSurface->SetFontGlyphSet( dwFontId , name , h , w , 0 , 0 , flag );
}

void cFont::DrawString( int x , int y , Color color , bool center , char* string )
{
	BSTR conv_string = _com_util::ConvertStringToBSTR( string );

	if ( center )
	{
		int wide , tall;
		g_pSurface->GetTextSize( dwFontId , conv_string , wide , tall );
		x -= wide / 2;
	}

	g_pSurface->DrawSetTextColor( color );
	g_pSurface->DrawSetTextFont( dwFontId );
	g_pSurface->DrawSetTextPos( x , y );
	g_pSurface->DrawPrintText( conv_string , lstrlenW( conv_string ) , FONT_DRAW_DEFAULT );

	SysFreeString( conv_string );
}

void cDrawing::DrawLine( Vector vStart , Vector vEnd , Color color )
{
	g_pSurface->DrawSetColor( color );
	g_pSurface->DrawLine( (int)vStart.x , (int)vStart.y , (int)vEnd.x , (int)vEnd.y );
}

void cDrawing::OutlinedRect( int x , int y , int w , int h , Color color )
{
	g_pSurface->DrawSetColor( color );
	g_pSurface->DrawOutlinedRect( x , y , x + w , y + h );
}

void cDrawing::FillArea( int x , int y , int w , int h , Color color )
{
	g_pSurface->DrawSetColor( color );
	g_pSurface->DrawFilledRect( x , y , x + w , y + h );
}

void cDrawing::DrawBox( int x , int y , int w , int h , Color color )
{
	// top
	FillArea( x , y , w , 1 , color );
	// right
	FillArea( x , y + 1 , 1 , h - 1 , color );
	// left
	FillArea( x + w - 1 , y + 1 , 1 , h - 1 , color );	
	// bottom
	FillArea( x , y + h - 1 , w - 1 , 1 , color );
}

void cDrawing::DrawOutlineBox( int x , int y , int w , int h , Color color , bool inBox )
{
	DrawBox( x , y , w , h , Color( 0 , 0 , 0 ) );
	DrawBox( x + 1 , y + 1 , w - 2 , h - 2 , color );

	if ( inBox )
		DrawBox( x + 2 , y + 2 , w - 4 , h - 4 , Color( 0 , 0 , 0 ) );
}

void cDrawing::DrawCoalBox( int x , int y , int w , int h , Color color )
{
	int iw = w / 4;
	int ih = h / 4;
	// top
	FillArea( x , y , iw , 1 , color );
	FillArea( x + w - iw , y , iw , 1 , color );
	// left
	FillArea( x , y + 1 , 1 , ih - 1 , color );
	FillArea( x , y + 1 + h - ih , 1 , ih - 1 , color );
	// right
	FillArea( x + w - 1 , y + 1 , 1 , ih - 1 , color );
	FillArea( x + w - 1 , y + 1 + h - ih , 1 , ih - 1 , color );
	// bottom
	FillArea( x , y + h , iw , 1 , color );
	FillArea( x + w - iw , y + h , iw , 1 , color );
}

void cDrawing::DrawOutlineCoalBox( int x , int y , int w , int h , Color color , bool inBox )
{
	int iw = w / 4;
	int ih = h / 4;
	// top left
	FillArea( x , y , iw , 1 , Color( 0 , 0 , 0 ) );
	FillArea( x + 1 , y + 1 , iw - 1 , 1 , color );
	// top right
	FillArea( x + w - iw , y , iw , 1 , Color( 0 , 0 , 0 ) );
	FillArea( x + w - iw , y + 1 , iw - 1 , 1 , color );
	// left top
	FillArea( x , y + 1 , 1 , ih - 1 , Color( 0 , 0 , 0 ) );
	FillArea( x + 1 , y + 1 , 1 , ih - 1 , color );
	// left bottom
	FillArea( x , y + 1 + h - ih , 1 , ih , Color( 0 , 0 , 0 ) );
	FillArea( x + 1 , y + 1 + h - ih , 1 , ih - 1 , color );
	// right top
	FillArea( x + w - 1 , y + 1 , 1 , ih - 1 , Color( 0 , 0 , 0 ) );
	FillArea( x + w - 2 , y + 1 , 1 , ih - 1 , color );
	// right bottom
	FillArea( x + w - 1 , y + 1 + h - ih , 1 , ih - 1 , Color( 0 , 0 , 0 ) );
	FillArea( x + w - 2 , y + 1 + h - ih , 1 , ih - 1 , color );
	// bottom left
	FillArea( x , y + h , iw , 1 , Color( 0 , 0 , 0 ) );
	FillArea( x + 1 , y + h - 1 , iw - 1 , 1 , color );
	// bottom right
	FillArea( x + w - iw , y + h , iw , 1 , Color( 0 , 0 , 0 ) );
	FillArea( x + w - iw , y + h - 1 , iw - 1 , 1 , color );
	// inBox
	if ( inBox )
	{
		// top left
		FillArea( x + 2 , y + 2 , iw - 2 , 1 , Color( 0 , 0 , 0 ) );
		// top right
		FillArea( x + w - iw , y + 2 , iw - 2 , 1 , Color( 0 , 0 , 0 ) );
		// left top
		FillArea( x + 2 , y + 3 , 1 , ih - 3 , Color( 0 , 0 , 0 ) );
		// left bottom
		FillArea( x + 2 , y + 1 + h - ih , 1 , ih - 3 , Color( 0 , 0 , 0 ) );
		// right top
		FillArea( x + w - 3 , y + 3 , 1 , ih - 3 , Color( 0 , 0 , 0 ) );
		// right bottom
		FillArea( x + w - 3 , y + 1 + h - ih , 1 , ih - 3 , Color( 0 , 0 , 0 ) );
		// bottom left
		FillArea( x + 2 , y + h - 2 , iw - 2 , 1 , Color( 0 , 0 , 0 ) );
		// bottom right
		FillArea( x + w - iw , y + h - 2 , iw - 2 , 1 , Color( 0 , 0 , 0 ) );
		// 3 pixel fix
		// top left
		FillArea( x + iw , y , 1 , 3 , Color( 0 , 0 , 0 ) );
		// top right
		FillArea( x + w - iw - 1 , y , 1 , 3 , Color( 0 , 0 , 0 ) );
		// left top
		FillArea( x , y + ih , 3 , 1 , Color( 0 , 0 , 0 ) );
		// left bottom
		FillArea( x , y + h - ih , 3 , 1 , Color( 0 , 0 , 0 ) );
		// right top
		FillArea( x + w - 3 , y + ih , 3 , 1 , Color( 0 , 0 , 0 ) );
		// right bottom
		FillArea( x + w - 3 , y + h - ih , 3 , 1 , Color( 0 , 0 , 0 ) );
		// bottom left
		FillArea( x + iw , y + h - 2 , 1 , 3 , Color( 0 , 0 , 0 ) );
		// bottom right
		FillArea( x + w - iw - 1 , y + h - 2 , 1 , 3 , Color( 0 , 0 , 0 ) );
	}
}

void cDrawing::DrawHorBar( int x , int y , int w , int h , int val , Color color1 , Color color2 )
{
	int size = ( w * val ) / 100;
	OutlinedRect( x , y , w , h , Color( 0 , 0 , 0 ) );
	FillArea( x + 1 , y + 1 , w - 2 , h - 2 , color2 );
	FillArea( x + 1 , y + 1 , size - 2 , h - 2 , color1 );
}

void cDrawing::DrawVerBar( int x , int y , int w , int h , int val , Color color1 , Color color2 )
{
	int size = ( h * val ) / 100;
	OutlinedRect( x , y , w , h , Color( 0 , 0 , 0 ) );
	FillArea( x + 1 , y + 1 , w - 2 , h - 2 , color2 );
	FillArea( x + 1 , y + 1 + h - size , w - 2 , size - 2 , color1 );
}