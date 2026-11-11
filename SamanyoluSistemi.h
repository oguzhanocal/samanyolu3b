
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SamanyoluSistemi.generated.h"

UCLASS()
class SAMANYOLU3B_API ASamanyoluSistemi : public AActor
{
    GENERATED_BODY()

public:
    ASamanyoluSistemi();

    virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY()
    USceneComponent* Root;

    UPROPERTY()
    UStaticMeshComponent* Gunes;

    UPROPERTY()
    UStaticMeshComponent* Dunya;

    UPROPERTY()
    UStaticMeshComponent* Mars;

    UPROPERTY()
    UStaticMeshComponent* Jupiter;

    UPROPERTY()
    UStaticMeshComponent* Saturn;

    UPROPERTY()
    UPointLightComponent* GunesIsigi;

    float Zaman = 0.0f;
};
