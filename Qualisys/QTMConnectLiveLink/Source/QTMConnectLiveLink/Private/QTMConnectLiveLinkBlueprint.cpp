// QTM Connect For Unreal. Copyright 2018-2020 Qualisys
//
#include "QTMConnectLiveLinkBlueprint.h"
#include "ILiveLinkClient.h"
#include "Features/IModularFeature.h"
#include "Features/IModularFeatures.h"
#include "QTMConnectLiveLinkSource.h"

void UQTMConnectLiveLinkBlueprint::CreateQTMConnectLiveLinkSource(FString IpAddress, bool AutoDiscover, FLiveLinkSourceHandle& SourceHandle)
{
    IModularFeatures& ModularFeatures = IModularFeatures::Get();

    TSharedPtr<FQTMConnectLiveLinkSource> livelinkSource = nullptr;
    if (ModularFeatures.IsModularFeatureAvailable(ILiveLinkClient::ModularFeatureName))
    {
        ILiveLinkClient* LiveLinkClient = &ModularFeatures.GetModularFeature<ILiveLinkClient>(ILiveLinkClient::ModularFeatureName);

        QTMConnectLiveLinkSettings settings;
        settings.IpAddress = IpAddress;
        settings.AutoDiscover = AutoDiscover;

        livelinkSource = MakeShareable(new FQTMConnectLiveLinkSource(settings));
        LiveLinkClient->AddSource(livelinkSource);
    }
    SourceHandle.SetSourcePointer(livelinkSource);
}
