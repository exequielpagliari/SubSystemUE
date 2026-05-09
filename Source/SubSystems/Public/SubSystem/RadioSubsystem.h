// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundWave.h"
#include "RadioSubsystem.generated.h"


/**
 * @class URadioSubsystem
 * @brief Subsistema encargado de la gestión y reproducción de audio persistente.
 *
 * Este subsistema hereda de UGameInstanceSubsystem, lo que garantiza que la música
 * no se interrumpa durante las transiciones de carga entre diferentes niveles (Seamless Travel o LoadLevel).
 *
 * Provee una interfaz para que los Blueprints puedan controlar listas de reproducción,
 * ajustar el volumen y responder a eventos de cambio de pista.
 *
 */
UCLASS()
class SUBSYSTEMS_API URadioSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

/**
 * @brief Carga una nueva lista de reproducción en el subsistema.
 *
 * Reemplaza la lista actual por una nueva colección de pistas.
 * Nota: Esto no detiene la reproducción actual de forma automática.
 *
 * @param NewTracks Arreglo de punteros a USoundBase (soporta SoundWaves y SoundCues).
 */
	UFUNCTION(BlueprintCallable, Category = "Radio")
	void LoadPlaylist(TArray<USoundBase*> NewTracks);

/**
 * @brief Reproduce la siguiente pista en la lista de reproducción.
 *
 * Incrementa el índice actual de forma circular (vuelve al inicio si llega al final).
 * Si el AudioComponent no está inicializado o registrado en el mundo actual,
 * esta función se encarga de asegurar su validez antes de la reproducción.
 */
	UFUNCTION(BlueprintCallable, Category = "Radio")
	void PlayNextTrack();

/**
 * @brief Detiene la reproducción de audio actual.
 *
 * Libera el recurso de audio del componente, pero mantiene el índice de la
 * pista actual para un posible reinicio.
 */
	UFUNCTION(BlueprintCallable, Category = "Radio")
	void StopRadio();

/**
 * @brief Ajusta el volumen del componente de radio.
 *
 * Se recomienda que el valor de entrada sea procesado mediante una curva
 * logarítmica antes de llamar a esta función para una percepción natural.
 *
 * @param Volume Multiplicador de volumen (rango sugerido 0.0 a 1.0).
 */
	UFUNCTION(BlueprintCallable, Category = "Radio")
	void SetRadioVolume(float Volume);

	


private:
	/**
 * @brief Componente de audio dinámico encargado de la salida de sonido.
 * Se gestiona manualmente para persistir a través de cambios de nivel.
 */
	UPROPERTY()
	UAudioComponent* RadioAudioComponent;
	/**
 * @brief Contenedor interno de las pistas de audio cargadas.
 */
	TArray<USoundBase*> Playlist;
	/**
 * @brief Índice de la pista que se está reproduciendo actualmente.
 * Inicializado en -1 para indicar que no hay reproducción activa.
 */
	int32 CurrentTrackIndex = -1;
	/**
 * @brief Callback disparado automáticamente cuando una pista finaliza su reproducción.
 *
 * Está vinculado al delegado OnAudioFinished del RadioAudioComponent para
 * permitir la reproducción continua.
 */
	UFUNCTION()
	void OnTrackFinished();
};
