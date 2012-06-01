/********************************************************************************** 
 
 Copyright (C) 2012 Syed Reza Ali (www.syedrezaali.com)
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 
 **********************************************************************************/

#ifndef OFXUI_TEXT_INPUT_IPHONE
#define OFXUI_TEXT_INPUT_IPHONE

#include "ofxUIWidgetWithLabel.h"
class ofxiPhoneKeyboard;

class ofxUITextInputIphone : public ofxUIWidget
{
public:
    ofxUITextInputIphone(float x, float y, float w, string _name, string _textstring, int _size, float h = 0)
    {
        rect = new ofxUIRectangle(x,y,w,h); 
        init(w, _name, _textstring, _size); 
    }
    
    ofxUITextInputIphone(float w, string _name, string _textstring, int _size, float h = 0)
    {
        rect = new ofxUIRectangle(0,0,w,h); 
        init(w, _name, _textstring, _size); 
    }    
    
    void init(float w, string _name, string _textstring, int _size);
    
    virtual void setDrawPadding(bool _draw_padded_rect)
	{
		draw_padded_rect = _draw_padded_rect; 
	}
    
    virtual void setDrawPaddingOutline(bool _draw_padded_rect_outline)
	{
		draw_padded_rect_outline = _draw_padded_rect_outline; 
	}  

	void enable();
	void disable();
	void update();
	
    virtual void drawFill() 
    {
        if(draw_fill)
        {
            ofFill(); 
            ofSetColor(color_fill); 
            rect->draw(); 
        }
    }
	
    void mouseMoved(int x, int y ) 
    {
        if(rect->inside(x, y))
        {
            state = OFX_UI_STATE_OVER;         			
        }    
        else
        {
            state = OFX_UI_STATE_NORMAL;        
            unClick(); 
        }
        stateChange();         
    }
    
    void mouseDragged(int x, int y, int button) 
    {
        if(hit)
        {
            state = OFX_UI_STATE_DOWN;         
        }    
        else
        {
            state = OFX_UI_STATE_NORMAL;  
            unClick(); 
        }
        stateChange();     
    }
    
    void mousePressed(int x, int y, int button) 
    {
        if(rect->inside(x, y))
        {
			if(state == OFX_UI_STATE_OVER)
			{
				clicked = true; 
				theta = 0; 
                hit = true; 
			}
#ifdef TARGET_OPENGLES
			clicked = true;
			theta = 0;
			hit = true;
#endif
            state = OFX_UI_STATE_DOWN;     
			triggerType = OFX_UI_TEXTINPUT_ON_FOCUS; 
			triggerEvent(this); 			
        }    
        else
        {
            state = OFX_UI_STATE_NORMAL;        
        }
        stateChange();         
    }
    
    void mouseReleased(int x, int y, int button) 
    {
        if(hit)
        {
#ifdef TARGET_OPENGLES
            state = OFX_UI_STATE_NORMAL;        
#else            
            state = OFX_UI_STATE_OVER; 
#endif 
//			triggerType = OFX_UI_TEXTINPUT_ON_UNFOCUS; 
//			triggerEvent(this); 
        }    
        else
        {
            state = OFX_UI_STATE_NORMAL;         
        }
        hit = false; 
        stateChange();         
    }
	    
    void unClick()
    {
        if(clicked)
        {
            clicked = false;          
			triggerType = OFX_UI_TEXTINPUT_ON_UNFOCUS; 
			triggerEvent(this);             
        }     
    }
    void stateChange()
    {        
        switch (state) {
            case OFX_UI_STATE_NORMAL:
            {            
                draw_fill_highlight = false;             
                draw_outline_highlight = false;  
            }
                break;
            case OFX_UI_STATE_OVER:
            {
                draw_fill_highlight = false;            
                draw_outline_highlight = true;  
            }
                break;
            case OFX_UI_STATE_DOWN:
            {
                draw_fill_highlight = false;            
                draw_outline_highlight = true;             
            }
                break;
            case OFX_UI_STATE_SUSTAINED:
            {
                draw_fill_highlight = false;            
                draw_outline_highlight = false;                         
            }
                break;                            
            default:
                break;
        }        
    }
	
    void setVisible(bool _visible)
    {
        visible = _visible; 
    }
    
	bool isClicked()
	{
		return clicked; 
	}

	string getTextString()
	{
		return textstring; 
	}
	
	int getTriggerType()
	{
		return triggerType; 
	}
	
	void setTextString(string s)	
	{
		textstring = s; 
	}
	
	void setParent(ofxUIWidget *_parent);
	
	void setAutoClear(bool _autoclear)
	{
		autoclear = _autoclear; 
	}

    
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
	string textstring; 
	string defaultstring; 
	bool clicked; 
	float theta; 
	float cursorWidth; 
	float spaceOffset;		
	bool autoclear; 
	float defaultY, defaultX; 	
	int triggerType;
    int maxsize; 
	
	ofxiPhoneKeyboard* keyboard;
	string previousKeyboardText;
}; 

#endif
