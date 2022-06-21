///////////////////////////////////////////
// Timer.cpp
//-----------------------------------------
// 2020/07/25	�쐬
//		08/29	Init�Ɉ����ǉ�
//
///////////////////////////////////////////

//--- �C���N���[�h��
#include "Timer.h"
#include "Polygon.h"

//--- ������
void CTimer::Init(int Num)
{
	m_nCount = Num;
	if (m_nCount == -1) return;

	m_polygon = new CPolygon();
	m_polygon->SetSize(30, 30);
	m_polygon->SetImage("Image/Number.png");
	m_polygon->SetSplit(5, 3);

	m_timer = new CPolygon();
	m_timer->SetSize(40, 40);
	m_timer->SetImage("Image/Timer.png");
	m_timer->SetPos(800, 50);
	m_timer->SetColor(1, 1, 1, 0.7f);
}

//--- �I��
void CTimer::Uninit()
{

}

//--- �X�V
bool CTimer::Update()
{
	if (m_nCount == -1) return false;

	// 0�ŃX�g�b�v
	if (m_nCount > 0)
	{
		m_nCount--;
	}
	else
	{
		// �J�E���g�_�E���I��
		return true;
	}

	return false;
}

//--- �`��
void CTimer::Draw()
{
	if (m_nCount == -1) return;

	m_timer->Draw();

	int number = m_nCount / 60;
	float x = 900;	// �`��J�n�ʒu

	do
	{
		m_polygon->SetUV((float)(number % 10 % 5), float(number % 10 / 5));

		if ((m_nCount / 60) % 10 == 0)
		{
			if (m_nCount / 60 <= 0)
			{
				m_polygon->SetColor(1.0f, 0.0f, 0.0f, 0.8f);
				m_polygon->SetSize(100, 100);
				m_polygon->SetPos(x, 50);
				m_polygon->Draw();
				break;
			}
			m_polygon->SetColor(1.0f, 1.0f, 0.0f, 0.8f);
			m_polygon->SetSize(60, 60);
			m_polygon->SetPos(x, 50);
			m_polygon->Draw();
			x -= 60;
		}
		else if (m_nCount / 60 < 10)
		{
			m_polygon->SetColor(1.0f, 0.0f, 0.0f, 0.8f);
			m_polygon->SetSize(100, 100);
			m_polygon->SetPos(x , 50);
			m_polygon->Draw();
		}
		else
		{
			m_polygon->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			m_polygon->SetSize(30, 30);
			m_polygon->SetPos(x, 50);
			m_polygon->Draw();

			x -= 30;
		}
		
		// �������炷
		number /= 10;

	} while (number > 0);

}
