// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GraphicsSubsystem.generated.h"

class UGameUserSettings;

/**
 * @class UGraphicsSubsystem
 * @brief Subsistema encargado de la gestión de configuraciones gráficas y rendimiento.
 *
 * Este subsistema actúa como una interfaz simplificada sobre UGameUserSettings, permitiendo
 * ajustar la resolución, niveles de escalabilidad y realizar benchmarks de hardware.
 */
UCLASS()
class SUBSYSTEMS_API UGraphicsSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    /**
     * @brief Define la resolución de pantalla y el modo de ventana.
     * @param Width Ancho en píxeles.
     * @param Height Alto en píxeles.
     * @param bFullscreen True para pantalla completa, False para modo ventana.
     */
    UFUNCTION(BlueprintCallable, Category = "Graphics|Settings")
    void SetResolution(int32 Width, int32 Height, bool bFullscreen);

    /**
     * @brief Obtiene la resolución actual configurada en el sistema.
     * @param OutWidth [Out] Referencia donde se guardará el ancho.
     * @param OutHeight [Out] Referencia donde se guardará el alto.
     * @param OutFullscreen [Out] Referencia donde se guardará el estado de pantalla completa.
     */
    UFUNCTION(BlueprintCallable, Category = "Graphics|Settings")
    void GetResolution(int32& OutWidth, int32& OutHeight, bool& OutFullscreen) const;

    /**
     * @brief Establece un nivel de calidad global para todos los grupos de escalabilidad.
     * @param QualityLevel Nivel de calidad (Normalmente 0=Bajo, 1=Medio, 2=Alto, 3=Ultra).
     */
    UFUNCTION(BlueprintCallable, Category = "Graphics|Scalability")
    void SetScalabilityGroup(int32 QualityLevel);

    /**
     * @brief Obtiene el nivel de calidad global actual.
     * @return Nivel de escalabilidad configurado.
     */
    UFUNCTION(BlueprintCallable, Category = "Graphics|Scalability")
    int32 GetScalabilityGroup() const;

    /**
     * @brief Confirma los cambios gráficos actuales, los aplica al motor y los guarda en el archivo de configuración (.ini).
     */
    UFUNCTION(BlueprintCallable, Category = "Graphics|Settings")
    void ApplyAndSaveSettings();

    /**
     * @brief Analiza el hardware del usuario y ajusta automáticamente los niveles de calidad para optimizar el rendimiento.
     */
    UFUNCTION(BlueprintCallable, Category = "Graphics|Hardware")
    void RunAutoBenchmark();

    /**
     * @brief Consulta al sistema operativo las resoluciones compatibles con el monitor principal.
     * @return TArray de FIntPoint conteniendo los pares Ancho x Alto disponibles.
     */
    UFUNCTION(BlueprintCallable, Category = "Graphics|Hardware")
    TArray<FIntPoint> GetAvailableScreenResolutions();

    /**
     * @brief Convierte un punto de resolución en una cadena de texto legible.
     * @param Resolution El punto de resolución (FIntPoint).
     * @return FString con el formato "Width x Height" (ej: "1920x1080").
     */
    UFUNCTION(BlueprintPure, Category = "Graphics|Utility")
    FString ResolutionToString(FIntPoint Resolution);

protected:
    /**
     * @brief Función auxiliar para obtener el puntero a UGameUserSettings de forma segura.
     * @return Puntero a la instancia actual de configuraciones de usuario del juego.
     */
    UGameUserSettings* GetSettings() const;
};