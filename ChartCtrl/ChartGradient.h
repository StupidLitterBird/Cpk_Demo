/*
 *
 *	ChartGradient.h
 *
 *	Written by C閐ric Moonen (cedric_moonen@hotmail.com)
 *
 *
 *
 *	This code may be used for any non-commercial and commercial purposes in a compiled form.
 *	The code may be redistributed as long as it remains unmodified and providing that the 
 *	author name and this disclaimer remain intact. The sources can be modified WITH the author 
 *	consent only.
 *	
 *	This code is provided without any garanties. I cannot be held responsible for the damage or
 *	the loss of time it causes. Use it at your own risks
 *
 *	An e-mail to notify me that you are using this code is appreciated also.
 *
 *
 */

#pragma once

//! Types of gradients that can be used
enum EGradientType
{
	//! A simple horizontal gradient (from the first color to the second)
	//一个简单的水平梯度（从第一个颜色到第二个）
	gtHorizontal,
	//! A simple Vertical gradient (from the first color to the second)
	//一个简单的垂直梯度（从第一个颜色到第二个）
	gtVertical,
	//! A double horizontal gradient (first color to second and back to first)
	//一个双水平梯度（第一颜色到第二和回第一）
	gtHorizontalDouble,
	//! A double vertical gradient (first color to second and back to first)
	//双垂直渐变（第一色到第二和回第一）
	gtVerticalDouble
};

//! Helper class to draw gradient.
/**
	It only contains a static function to draw the gradient. This is
	mainly used internally.
**/
class CChartGradient
{
public:
	//! Constructor
	CChartGradient();
	//! Destructor
	~CChartGradient();

	//! Draws a gradient between two colors inside a rectangle.
	/**
		@param pDC
			The device context with which to draw.
		@param GradientRect
			The rectangle in which to draw the gradient
		@param Color1
			The first gradient color
		@param Color2
			The second gradient color
		@param GradientType
			The type of gradient to use in the rectangle
	**/
	static void DrawGradient(CDC* pDC, const CRect& GradientRect, COLORREF Color1, 
							 COLORREF Color2, EGradientType GradientType);
};
