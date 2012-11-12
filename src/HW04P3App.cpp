/* HW04 Phase 3
 * The bulk of the fancy animations were borrowed from the _svg examples in Cinder, I take no credit for them.
 * I wish I had discovered them sooner, because this might have actually been a full solution.
 *
 */

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/TextureFont.h"
#include "cinder/svg/Svg.h"
#include "cinder/cairo/Cairo.h"
#include "cinder/Timeline.h"
#include <iostream>
#include <fstream>
#include <string>
#include "anglesswStarbucks.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class HW04P3App : public AppBasic {
  public:
  	void prepareSettings( Settings *settings );
	void setup();
	void mouseMove( MouseEvent event );	
	void mouseDown( MouseEvent event );
	void draw();
	
	gl::Texture			mMapTex;
	gl::TextureFontRef	mFont;
	svg::DocRef			mMapDoc;
	svg::Node 			*mCurrentCountry;
	Anim<float>			mCurrentCountryAlpha;

	int index;
	Entry* entry_arr;
	Entry* nearestEntry;
	anglesswStarbucks* starbucks;
};

gl::Texture renderSvgToTexture( svg::DocRef doc, Vec2i size )
{
	cairo::SurfaceImage srf( size.x, size.y, false );
	cairo::Context ctx( srf );
	ctx.render( *doc );
	srf.flush();
	return gl::Texture( srf.getSurface() );
}

void HW04P3App::prepareSettings( Settings *settings )
{
	settings->setResizable( false );
	settings->setWindowSize( 959, 593 );
}

void HW04P3App::setup()
{
	mMapDoc = svg::Doc::create( loadAsset( "Blank_US_Map_48states.svg" ) );
	mMapTex = renderSvgToTexture( mMapDoc, getWindowSize() );
	
	mFont = gl::TextureFont::create( Font( loadAsset( "Dosis-Medium.ttf" ), 36 ) );
	
	mCurrentCountry = 0;
	
	//Begin starbucks stuff
	ifstream in_file("Starbucks_2006.csv");

	index = 0;

	entry_arr = new Entry[7700];

	while(in_file.eof() != true) {
		getline(in_file,entry_arr[index].identifier,',');

		in_file >> entry_arr[index].x;

		in_file.get();

		in_file >> entry_arr[index].y;

		in_file.get();

		index++;
	}

	in_file.close();
	delete in_file;

	starbucks = new anglesswStarbucks();
	starbucks->build(entry_arr,index);

	nearestEntry = 0;
}

void HW04P3App::mouseMove( MouseEvent event )
{
	svg::Node *newNode = mMapDoc->nodeUnderPoint( event.getPos() );
	if( newNode != mCurrentCountry )
		timeline().apply( &mCurrentCountryAlpha, 0.0f, 1.0f, 0.35f );
	mCurrentCountry = newNode;
	// if the current node has no name just set it to NULL
	if( mCurrentCountry && mCurrentCountry->getId().empty() )
		mCurrentCountry = NULL;	
}

void HW04P3App::mouseDown( MouseEvent event )
{
	nearestEntry = starbucks->getNearest((double) event.getPos().x/getWindowSize().x,(double) (1-event.getPos().y/getWindowSize().y));
}

void HW04P3App::draw()
{
	gl::enableAlphaBlending();
	glLineWidth( 2.0f );
	
	if( mMapTex ) {
		gl::color( Color::white() );
		gl::draw( mMapTex );
	}

	if( mCurrentCountry ) {
		// draw the outline
		gl::color( 1, 0.5f, 0.25f, mCurrentCountryAlpha );
		gl::draw( mCurrentCountry->getShapeAbsolute() );
	
		// draw the name
		string countryName = mCurrentCountry->getId();
		Vec2f pos = mCurrentCountry->getBoundingBoxAbsolute().getCenter();
		pos.x -= mFont->measureString( countryName ).x / 2;
		
		gl::color( ColorA( 1, 1, 1, mCurrentCountryAlpha ) );
		mFont->drawString( countryName, pos + Vec2f( 2, 2 ) );
		gl::color( ColorA( 0, 0, 0, mCurrentCountryAlpha ) );
		mFont->drawString( countryName, pos );		
	}

	for(int i=0;i<index;i++) {
		gl::color(ColorA(0.5,0.5,0.5,0.5));
		gl::drawSolidCircle(Vec2f(35+entry_arr[i].x*getWindowSize().x,(1-entry_arr[i].y)*getWindowSize().y),1);
	}

	if(nearestEntry) {
		gl::color(ColorA(1.0,1.0,1.0,0.5));
		gl::drawSolidCircle(Vec2f(35+nearestEntry->x*getWindowSize().x,(1-nearestEntry->y)*getWindowSize().y),20);
	}
	else
		return;
}


CINDER_APP_BASIC( HW04P3App, RendererGl(0) )
