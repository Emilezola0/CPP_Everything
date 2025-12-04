// Fill out your copyright notice in the Description page of Project Settings.


#include "CBP_WFL_StairsRight.h"

// Sets default values
ACBP_WFL_StairsRight::ACBP_WFL_StairsRight()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    StairsRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRootComponent"));
    RootComponent = StairsRoot;

    CubeCount = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Total Cubes"));
    CubeCount->SetupAttachment(StairsRoot);

    HISM_Stair = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("MainHISM"));
    HISM_Stair->SetupAttachment(StairsRoot);

    //Default Values
    bRenderText = true;
    StonesX = 5.0f;
    StonesZ = 5.0f;
    StoneZOffset = 50.0f;
    CubesTotal = 0.0f;
}

void ACBP_WFL_StairsRight::OnConstruction(const FTransform& Transform)
{

    if (!SM_Stone) return;


    HISM_Stair->ClearInstances();
    HISM_Stair->SetStaticMesh(SM_Stone);


    if (BpName) BpName->SetVisibility(bRenderText);
    if (CubeCount) CubeCount->SetVisibility(bRenderText);


    MeshBounds = (SM_Stone->GetBoundingBox().Max - SM_Stone->GetBoundingBox().Min);


    int LoopX = StonesX;
    int MaxHeightZ = StonesZ;

    // 3. Boucles de génération
    for (int32 x = 0; x < LoopX; x++)
    {
        // Calcul de la position X
        float XPos = x * MeshBounds.X;

        // Déterminer la hauteur de la colonne actuelle. 
        // L'escalier monte (x + 1) mais ne doit pas dépasser la hauteur max (MaxHeightZ)
        int32 CurrentColumnHeight = FMath::Min(x + 1, MaxHeightZ);

        for (int32 z = 0; z < CurrentColumnHeight; z++)
        {
            float ZPos = (z * MeshBounds.Z) + StoneZOffset;

            // CRITIQUE : Scale mis à 1.0f (FVector::OneVector)
            FTransform InstanceTransform;
            InstanceTransform.SetLocation(FVector(XPos, 0.0f, ZPos));
            InstanceTransform.SetRotation(FQuat::Identity);
            InstanceTransform.SetScale3D(FVector(1.0f));

            HISM_Stair->AddInstance(InstanceTransform);
        }
    }

    // 4. Mise à jour du texte
    if (CubeCount)
    {
        // On récupère le vrai nombre d'instances créées
        int32 RealCount = HISM_Stair->GetInstanceCount();
        FString Str = FString::Printf(TEXT("Cube Count : %d"), RealCount);
        CubeCount->SetText(FText::FromString(Str));
    }
}

// Called when the game starts or when spawned
void ACBP_WFL_StairsRight::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void ACBP_WFL_StairsRight::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

