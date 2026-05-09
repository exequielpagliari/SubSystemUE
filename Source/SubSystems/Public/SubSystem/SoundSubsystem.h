// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Sound/SoundMix.h"   
#include "Sound/SoundClass.h" 
#include "SoundSubsystem.generated.h"

/**
 * @class USoundSubsystem
 * @brief Subsistema encargado de la gestión global del volumen y la mezcla de sonido.
 *
 * Este subsistema permite controlar de forma independiente los volúmenes de Master, Música y SFX
 * mediante el uso de Sound Mixes y Sound Classes. Persiste durante toda la vida de la GameInstance.
 */
UCLASS(Blueprintable)
class SUBSYSTEMS_API USoundSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	/** @brief Referencia al Sound Mix principal que controla las jerarquías de sonido. */
	UPROPERTY(EditAnywhere, Category = "Sound | Config")
	TObjectPtr<USoundMix> MainSoundMix;

	/** @brief Referencia a la clase de sonido Master (padre de todas). */
	UPROPERTY(EditAnywhere, Category = "Sound | Config")
	TObjectPtr<USoundClass> MasterClass;

	/** @brief Referencia a la clase de sonido que agrupa la música. */
	UPROPERTY(EditAnywhere, Category = "Sound | Config")
	TObjectPtr<USoundClass> MusicClass;

	/** @brief Referencia a la clase de sonido que agrupa los efectos de sonido. */
	UPROPERTY(EditAnywhere, Category = "Sound | Config")
	TObjectPtr<USoundClass> SFXClass;

	/** @brief Obtiene el volumen actual del canal Master. @return float en rango [0.0 - 1.0]. */
	UFUNCTION(BlueprintCallable, Category = "Sound | Get")
	inline float GetMasterVolume() const { return MasterVolume; }

	/** @brief Obtiene el volumen actual del canal de Música. @return float en rango [0.0 - 1.0]. */
	UFUNCTION(BlueprintCallable, Category = "Sound | Get")
	inline float GetMusicVolume() const { return MusicVolume; }

	/** @brief Obtiene el volumen actual del canal de Efectos (SFX). @return float en rango [0.0 - 1.0]. */
	UFUNCTION(BlueprintCallable, Category = "Sound | Get")
	inline float GetSFXVolume() const { return SFXVolume; }

	/**
	 * @brief Actualiza el volumen Master y aplica el override al mezclador.
	 * @param NewVolume Nuevo volumen en rango [0.0 - 1.0].
	 */
	UFUNCTION(BlueprintCallable, Category = "Sound | Set")
	void SetMasterVolume(float NewVolume);

	/**
 * @brief Actualiza el volumen de Master de manera logarítmica y aplica el override al mezclador.
 * @param LinearVolume Nuevo volumen lineal en rango [0.0 - 1.0].
 */
	UFUNCTION(BlueprintCallable, Category = "Sound | Set")
	void SetMasterVolumeLogarithmic(float LinearVolume);

	/**
	 * @brief Actualiza el volumen de Música y aplica el override al mezclador.
	 * @param NewVolume Nuevo volumen en rango [0.0 - 1.0].
	 */
	UFUNCTION(BlueprintCallable, Category = "Sound | Set")
	void SetMusicVolume(float NewVolume);

	/**
	 * @brief Actualiza el volumen de Música de manera logarítmica y aplica el override al mezclador.
	 * @param LinearVolume Nuevo volumen lineal en rango [0.0 - 1.0].
	 */
	UFUNCTION(BlueprintCallable, Category = "Sound | Set")
	void SetMusicVolumeLogarithmic(float LinearVolume);

	/**
	 * @brief Actualiza el volumen de SFX y aplica el override al mezclador.
	 * @param NewVolume Nuevo volumen en rango [0.0 - 1.0].
	 */
	UFUNCTION(BlueprintCallable, Category = "Sound | Set")
	void SetSFXVolume(float NewVolume);

	/**
 * @brief Actualiza el volumen de SFX de manera logarítmica y aplica el override al mezclador.
 * @param LinearVolume Nuevo volumen lineal en rango [0.0 - 1.0].
 */
	UFUNCTION(BlueprintCallable, Category = "Sound | Set")
	void SetSFXVolumeLogarithmic(float LinearVolume);

	/** @brief Asigna un nuevo Sound Mix como mezclador principal. @param NewSoundMix Puntero al nuevo asset de Sound Mix. */
	UFUNCTION(BlueprintCallable, Category = "Sound | Set")
	void SetMainSoundMix(USoundMix* NewSoundMix);

	/** @brief Asigna el asset de Sound Class para el canal Master. @param NewSoundClass Puntero al asset de Sound Class. */
	UFUNCTION(BlueprintCallable, Category = "Sound | Set")
	void SetMasterSoundClass(USoundClass* NewSoundClass);

	/** @brief Asigna el asset de Sound Class para el canal de Música. @param NewSoundClass Puntero al asset de Sound Class. */
	UFUNCTION(BlueprintCallable, Category = "Sound | Set")
	void SetMusicSoundClass(USoundClass* NewSoundClass);

	/** @brief Asigna el asset de Sound Class para el canal de SFX. @param NewSoundClass Puntero al asset de Sound Class. */
	UFUNCTION(BlueprintCallable, Category = "Sound | Set")
	void SetSFXSoundClass(USoundClass* NewSoundClass);

	/**
	 * @brief Ejecuta el cambio técnico en el motor de audio de Unreal.
	 * @param InSoundMix El mezclador sobre el que actuar.
	 * @param InSoundClass La clase de sonido a la que aplicar el volumen.
	 * @param NewVolume El valor de volumen a aplicar.
	 */
	UFUNCTION(BlueprintCallable, Category = "Sound | Set")
	void UpdateMixer(USoundMix* InSoundMix, USoundClass* InSoundClass, float NewVolume);

private:
	/** @brief Almacenamiento interno del volumen Master. */
	float MasterVolume = 1.f;
	/** @brief Almacenamiento interno del volumen de Música. */
	float MusicVolume = 1.f;
	/** @brief Almacenamiento interno del volumen de SFX. */
	float SFXVolume = 1.f;
};
