

#include "ofxUI.h"
#include "ofxUITextInputIphone.h"
#include "ofxiPhoneKeyboard.h"



void ofxUITextInputIphone::init(float w, string _name, string _textstring, int _size)
{

	name = _name; 		
	kind = OFX_UI_WIDGET_TEXTINPUT_IPHONE; 		
	textstring = _textstring; 
	defaultstring = _textstring; 
	//displaystring = _textstring; 
	
	paddedRect = new ofxUIRectangle(-padding, -padding, w+padding*2.0, padding*2.0);
	paddedRect->setParent(rect); 
	
	clicked = false;                                            //the widget's value
	autoclear = true; 
	
	/*
	label = new ofxUILabel(padding*2.0,0,(name+" LABEL"), _size); 
	label->setParent(label); 
	label->setRectParent(rect); 
	label->setEmbedded(true);
	 */
	
	triggerType = OFX_UI_TEXTINPUT_ON_FOCUS;
	cursorWidth = 0; spaceOffset = 0; 		
	theta = 0;         
	
	NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
	keyboard = new ofxiPhoneKeyboard( 0, 52, 320, 32 );
	keyboard->setVisible(false);
	keyboard->setBgColor(255, 255, 255, 255);
	keyboard->setFontColor(0,0,0, 255);
	int fontSize;
	if ( _size == OFX_UI_FONT_SMALL )
		fontSize = 12;
	else if ( _size == OFX_UI_FONT_MEDIUM )
		fontSize = 16;
	else {
		fontSize = 22;
	}
	keyboard->setFontSize(fontSize);
	ofLogNotice("ofxUI", "iphone setting keyboard text to "+_textstring);
	keyboard->setText(_textstring);
	previousKeyboardText = keyboard->getText();

	[pool drain];

}

void ofxUITextInputIphone::setParent(ofxUIWidget *_parent)
{
	parent = _parent; 
	if(rect->height == 0)
	{
		rect->height = 32.0f;
	}
	/*
	if(rect->height == 0)
	{
		rect->height = label->getPaddingRect()->height+padding*2.0; 
	}
	label->setLabel(textstring);
	ofxUIRectangle *labelrect = label->getRect(); 
	float h = labelrect->getHeight(); 
	float ph = rect->getHeight(); 	
	
	labelrect->y = ph/2.0 - h/2.0; 
	defaultY = labelrect->y+labelrect->getHeight(); 
	defaultX = labelrect->x; 
	*/
	paddedRect->height = rect->height+padding*2.0; 
	/*
	cursorWidth = label->getStringWidth("."); 
	
	while(label->getStringWidth(textstring) > rect->width-padding*4.0)
	{
		string::iterator it;
		it=textstring.begin();
		textstring.erase (it);                    
	}        */
	
	defaultstring = textstring; 
//	displaystring = textstring; 
	setTextString(textstring);      

	/*
	keyboard->setSize( rect->width, rect->height );
	keyboard->setPosition( rect->x, rect->y );
	 */
	

}	

void ofxUITextInputIphone::update()
{
	NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
	if ( keyboard->getText() != previousKeyboardText )
	{
		ofLogNotice("ofxUI", "keyboard text '"+keyboard->getText()+"', self '" + getTextString() +"'" );
		setTextString(keyboard->getText());
		triggerType = OFX_UI_TEXTINPUT_ON_ENTER; 					
		triggerEvent(this); 	
		
		previousKeyboardText = keyboard->getText();
	}

	[pool drain];
}


void ofxUITextInputIphone::enable()
{
	keyboard->setVisible(true);
	ofLogNotice("keyboard pos: "+ofToString(rect->width)+"x"+ofToString(rect->height)+" ("+ofToString(rect->x)+","+ofToString(rect->y) );
	keyboard->setSize( rect->width, rect->height );
	keyboard->setPosition( rect->x, rect->y+rect->height );
}
void ofxUITextInputIphone::disable()
{
	keyboard->setVisible(false);
}
