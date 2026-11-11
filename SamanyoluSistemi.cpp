
#include "SamanyoluSistemi.h"

#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "UObject/ConstructorHelpers.h"

ASamanyoluSistemi::ASamanyoluSistemi()
{
    PrimaryActorTick.bCanEverTick = true;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    SetRootComponent(Root);

    ConstructorHelpers::FObjectFinder<UStaticMesh> Sphere(
        TEXT("/Engine/BasicShapes/Sphere.Sphere")
    );

    ConstructorHelpers::FObjectFinder<UMaterialInterface> Material(
        TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial")
    );

    auto GezegenOlustur = [&](const TCHAR* Ad, float Boyut,
                              FLinearColor Renk)
    {
        UStaticMeshComponent* Yeni = CreateDefaultSubobject<UStaticMeshComponent>(Ad);

        Yeni->SetupAttachment(Root);

        if (Sphere.Succeeded())
            Yeni->SetStaticMesh(Sphere.Object);

        Yeni->SetRelativeScale3D(FVector(Boyut));

        if (Material.Succeeded())
        {
            UMaterialInstanceDynamic* Mat =
                UMaterialInstanceDynamic::Create(Material.Object, this);

            Mat->SetVectorParameterValue(TEXT("Color"), Renk);
            Yeni->SetMaterial(0, Mat);
        }

        return Yeni;
    };

    Gunes = GezegenOlustur(
        TEXT("Gunes"), 4.0f,
        FLinearColor(1.0f, 0.55f, 0.05f)
    );

    Dunya = GezegenOlustur(
        TEXT("Dunya"), 0.7f,
        FLinearColor(0.05f, 0.25f, 1.0f)
    );

    Mars = GezegenOlustur(
        TEXT("Mars"), 0.5f,
        FLinearColor(0.9f, 0.15f, 0.05f)
    );

    Jupiter = GezegenOlustur(
        TEXT("Jupiter"), 1.5f,
        FLinearColor(0.8f, 0.55f, 0.3f)
    );

    Saturn = GezegenOlustur(
        TEXT("Saturn"), 1.2f,
        FLinearColor(0.85f, 0.75f, 0.5f)
    );

    GunesIsigi = CreateDefaultSubobject<UPointLightComponent>(
        TEXT("GunesIsigi")
    );

    GunesIsigi->SetupAttachment(Root);
    GunesIsigi->SetIntensity(50000.0f);
    GunesIsigi->SetAttenuationRadius(10000.0f);
    GunesIsigi->SetLightColor(FLinearColor(1.0f, 0.85f, 0.6f));

    Dunya->SetRelativeLocation(FVector(900, 0, 0));
    Mars->SetRelativeLocation(FVector(1400, 0, 0));
    Jupiter->SetRelativeLocation(FVector(2100, 0, 0));
    Saturn->SetRelativeLocation(FVector(2800, 0, 0));
}

void ASamanyoluSistemi::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    Zaman += DeltaTime;

    auto YörüngeHareketi = [&](UStaticMeshComponent* Gezegen,
                               float Mesafe, float Hiz, float Aci)
    {
        float Radyan = FMath::DegreesToRadians(
            Zaman * Hiz + Aci
        );

        FVector Konum(
            FMath::Cos(Radyan) * Mesafe,
            FMath::Sin(Radyan) * Mesafe,
            0
        );

        Gezegen->SetRelativeLocation(Konum);

        Gezegen->AddLocalRotation(
            FRotator(0, 25.0f * DeltaTime, 0)
        );
    };

    YörüngeHareketi(Dunya, 900, 12, 0);
    YörüngeHareketi(Mars, 1400, 8, 45);
    YörüngeHareketi(Jupiter, 2100, 4, 90);
    YörüngeHareketi(Saturn, 2800, 2, 135);
}
