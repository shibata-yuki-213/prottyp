/*==============================================================================

   タイトル画面処理 [Result.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "Result.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "sound.h"
#include "fade.h" 

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int g_TextureBgTitle;//タイトル画面用テクスチャの識別子
static int g_BGMNo;//タイトル用BGMの識別子

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitResult(void)
{
	g_TextureBgTitle = LoadTexture((char*)"data/TEXTURE/Back_Clear.png");
	
	g_BGMNo = LoadSound((char*)"data/BGM/BGM_Result.wav");
	PlaySound(g_BGMNo, -1);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitResult(void)
{
	StopSound(g_BGMNo);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateResult(void)
{
	//エンターキーが押されたらSCENE_GAMEへ移行する
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		SceneTransition(SCENE_TITLE);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawResult(void)
{
	DrawSpriteLeftTop(g_TextureBgTitle, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f);
}
