#pragma once

#include <string>
#include <memory>
#include "ADX2Le.h"

namespace NYLibrary
{
	/*
	// @class		SoundManager �N���X�iSingleton�j
	// @content		�T�E���h�}�l�[�W��
	// @use			
	*/
	class SoundManager 
	{
	private:

		static std::unique_ptr<SoundManager> soundManager;
		SoundManager() = default;

	public:
		static SoundManager* GetInstance()
		{
			if (!soundManager.get())
			{
				soundManager.reset(new SoundManager);
			}

			return soundManager.get();
		}

		/*
		// @method		Initialize
		// @content		����������
		// @param		Acf�t�@�C�����istring�j
		// @param		Acb�t�@�C�����istring�j
		// @param		Awb�t�@�C�����istring�j
		*/
		void Initialize(std::string acf, std::string acb, std::string awb)
		{
			static const std::string FILE_PATH_SOUND = "Resources/Sounds/";
			static const std::string EXT_ACF = ".acf";
			static const std::string EXT_ACB = ".acb";
			static const std::string EXT_AWB = ".awb";

			// �t�@�C�����̎w��
			std::string filePathAcf = FILE_PATH_SOUND + acf + EXT_ACF;
			std::string filePathAcb = FILE_PATH_SOUND + acb + EXT_ACB;
			std::string filePathAwb = FILE_PATH_SOUND + awb + EXT_AWB;

			// �T�E���h�f�[�^�̓ǂݍ���
			ADX2Le::Initialize(filePathAcf.c_str());
			ADX2Le::LoadAcb(filePathAcb.c_str(), filePathAwb.c_str());
		}

		/*
		// @method		Update
		// @content		�X�V����
		*/
		void Update()
		{
			ADX2Le::Update();
		}

		/*
		// @method		PlayAudio
		// @content		���̍Đ�
		// @param		�L���[ID�iint�j
		*/
		void PlayAudio(int audioID)
		{
			ADX2Le::Play(audioID);
		}

		/*
		// @method		StopAudio
		// @content		���̒�~
		*/
		void StopAudio()
		{
			ADX2Le::Stop();
		}

		/*
		// @method		Dispose
		// @content		�I������
		*/
		void Dispose()
		{
			ADX2Le::Finalize();
		}
	};


}

