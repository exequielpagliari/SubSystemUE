# SubSystemsUE

Este proyecto implementa una arquitectura basada en Subsystems de Unreal Engine para gestionar el flujo de la aplicación. El objetivo principal es evitar la creación de una clase GameInstance masiva ("God Object"), delegando responsabilidades específicas a módulos independientes y persistentes.

## Arquitectura: Subsystems vs. GameInstance

Para mantener la escalabilidad y limpieza del código, el flujo se divide en diversos subsistemas. Esto permite que cada módulo maneje su propio estado y lógica sin interferir con los demás.

## Subsystems Implementados

SoundSubsystem: Gestiona el control de volumen (Master, Música, SFX) mediante SoundMix y SoundClass overrides. Permite cambios en tiempo real y comunicación directa con la UI.

## Créditos de Audio y Copyright

Este proyecto utiliza recursos de audio externos bajo licencias Creative Commons. Para cumplir con los términos de la licencia Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0), se detallan los créditos a continuación:

Pista: Temple Procession (ID 1421).
Artista: Lobo Loco.
Álbum: Spaceforce OMEGA.
Licencia: CC BY-NC-SA 4.0.

Nota: El uso de este material está restringido a fines no comerciales. Cualquier trabajo derivado debe ser compartido bajo la misma licencia.
