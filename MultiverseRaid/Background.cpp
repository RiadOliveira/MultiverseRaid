/**********************************************************************************
// Background (C�digo Fonte)
// 
// Cria��o:     07 Dez 2011
// Atualiza��o: 01 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Representa um pano de fundo maior que a janela
//
**********************************************************************************/


#include "Background.h"
#include "WizardAvatar.h"
#include "Engine.h"

// -------------------------------------------------------------------------------

Background::Background(string filename)
{
    // carrega imagem
    image = new Image(filename);

    // configura registro spriteData
    spriteData.x = Engine::window->CenterX();
    spriteData.y = Engine::window->CenterY();
    spriteData.depth = Layer::BACK;
    spriteData.scale = 1.0f;    
    spriteData.rotation = 0.0f;
    spriteData.color = Color(1, 1, 1, 1);
    spriteData.texture = image->View();
}

// -------------------------------------------------------------------------------

Background::~Background()
{
    delete image;
}

// -------------------------------------------------------------------------------

void Background::Draw(ViewPort & vp, Color color)
{ 
    // define um sprite com a regi�o do pano de fundo limitada pela viewport
    spriteData.width = uint(vp.right - vp.left);
    spriteData.height = uint(vp.bottom - vp.top);
    spriteData.texCoord.x = vp.left / float(image->Width());
    spriteData.texCoord.y = vp.top / float(image->Height());
    spriteData.texSize.x = spriteData.width / float(image->Width());
    spriteData.texSize.y = spriteData.height / float(image->Height());
    spriteData.color = color;

    // adiciona o sprite na lista de desenho
    Engine::renderer->Draw(spriteData);
}

// -------------------------------------------------------------------------------

