/*==============================================================================

   タイトル画面処理 [Result.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "Result.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"
//#include "input.h"
#include "inputx.h"
#include "sound.h"
#include "fade.h" 
#include "keyboard.h"

#include "score.h"

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
static int g_TextureShishamo;
static int g_TextureClear;
static int g_TextureRankCoin;
static int g_BGMNo;//タイトル用BGMの識別子

PLAYER* pPlayerOne = GetPlayer();
SCORE* pScore = GetScore();

COIN g_Coin;

float	Shishamo_pos;
float	Shishamo_spd;
int Addcol;

bool	moving;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitResult(void)
{
	g_Coin.col = D3DXCOLOR(0.0f,0.0f,0.0f,1.0f);
	g_Coin.rad = 0.0f;
	g_Coin.u = 0.0f;
	g_Coin.u = 0.0f;

	g_TextureRankCoin= LoadTexture((char*)"data/TEXTURE/rank_coins_1200x200.png");
	g_TextureClear = LoadTexture((char*)"data/TEXTURE/text_clear.png");
	if (pPlayerOne->dead)
	{
		g_TextureClear = LoadTexture((char*)"data/TEXTURE/text_failed.png");
	}
	g_TextureBgTitle = LoadTexture((char*)"data/TEXTURE/Back.JPG");
	g_TextureShishamo = LoadTexture((char*)"data/TEXTURE/Shishamo_end_1.png");


	if (pScore->ToResult >= 0)
	{
		g_Coin.rank = 5;
	}
	if (pScore->ToResult >= 4000)
	{
		g_Coin.rank = 4;
	}
	if (pScore->ToResult >= 8000)
	{
		g_Coin.rank = 3;
	}
	if (pScore->ToResult >= 12000)
	{
		g_Coin.rank = 2;
	}
	if (pScore->ToResult >= 16000)
	{
		g_Coin.rank = 1;
	}
	if (pScore->ToResult >= 20000)
	{
		g_Coin.rank = 0;
	}



	InitScoreResult();

	Shishamo_pos = -450.0f;
	Shishamo_spd = 85.0f;
	Addcol = 0;
	moving = true;
	//g_BGMNo = LoadSound((char*)"data/BGM/BGM_Result.wav");
	//PlaySound(g_BGMNo, -1);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitResult(void)
{
	UninitPlayer();
	UninitScore();
	StopSound(g_BGMNo);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateResult(void)
{
	//エンターキーが押されたらSCENE_TITLEへ移行する
	if (Keyboard_IsKeyDown(KK_ENTER))
	{
		SceneTransition(SCENE_TITLE);
	}
	//コントローラーBボタン押したらSCENE_TITLEへ移行
	if (IsButtonTriggered(0, XINPUT_GAMEPAD_B))
	{
		SceneTransition(SCENE_TITLE);
	}

	//ししゃも移動
	if (moving)
	{
		Shishamo_pos += Shishamo_spd;	//スピードを足して移動
		Shishamo_spd *= 0.9f;			//スピード減衰
	}
	//移動完了
	if (Shishamo_spd <= 1.0f)
	{
		moving = false;
	}

	if (Addcol < 100)
	{
		Addcol++;
	}
	if (g_Coin.rad<=360*2-10)
	{
		g_Coin.rad+=10.0f;
	}
	g_Coin.col = D3DXCOLOR(0.0f + Addcol * 0.01f,
		0.0f + Addcol * 0.01f,
		0.0f + Addcol * 0.01f,
		1.0f);

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawResult(void)
{
	DrawSpriteLeftTop(g_TextureBgTitle, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteColor(g_TextureShishamo, Shishamo_pos, CENTER_Y, 800.0f, 800.0f,
		0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 1.0));

	DrawSpriteColor(g_TextureClear, CENTER_X, CENTER_Y-300.0f, 600.0f, 100.0f,
		0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 1.0));


	GetDeviceContext()->PSSetShaderResources(0, 1,
		GetTexture(g_TextureRankCoin));
	for (int i = 0; i < SCOER_DIGIT; i++) {
		DrawSpriteColorRotation(
			CENTER_X,
			CENTER_Y,
			300.0f,
			300.0f,
			g_Coin.rad,
			g_Coin.col,
			g_Coin.rank,
			0.16665f,
			1.0f,
			6
		);
	}

	DrawScore();
}
