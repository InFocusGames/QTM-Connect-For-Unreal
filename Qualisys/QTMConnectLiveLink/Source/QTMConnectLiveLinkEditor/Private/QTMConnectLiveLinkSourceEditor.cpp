// QTM Connect For Unreal. Copyright 2018-2020 Qualisys
//
#include "QTMConnectLiveLinkSourceEditor.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SSeparator.h"
#include "Widgets/Input/SNumericEntryBox.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Input/SCheckBox.h"

#define LOCTEXT_NAMESPACE "QTMConnectLiveLinkSourceEditor"

SQTMConnectLiveLinkSourceEditor::~SQTMConnectLiveLinkSourceEditor()
{
}

void SQTMConnectLiveLinkSourceEditor::Construct(const FArguments& Args)
{
    OnPropertiesSelected = Args._OnPropertiesSelected;

    ChildSlot
    [
        SNew(SBox)
        .WidthOverride(250)
        .HeightOverride(220)
        [
            SNew(SVerticalBox)

            + SVerticalBox::Slot()
            .AutoHeight()
            .Padding(3.0f)
            [
                SNew(SHorizontalBox)
                + SHorizontalBox::Slot()
                .HAlign(HAlign_Left)
                .FillWidth(0.5f)
                [
                    SNew(STextBlock)
                    .Text(LOCTEXT("AutoDiscover", "AutoDiscover"))
                ]
                + SHorizontalBox::Slot()
                .HAlign(HAlign_Fill)
                .FillWidth(0.5f)
                [
                    SAssignNew(AutoDiscoverCB, SCheckBox)
                    .IsChecked(ECheckBoxState::Checked)
                ]
            ]

            + SVerticalBox::Slot()
            .AutoHeight()
            .Padding(3.0f)
            [
                SNew(SHorizontalBox)
                + SHorizontalBox::Slot()
                .HAlign(HAlign_Left)
                .FillWidth(0.5f)
                [
                    SNew(STextBlock)
                    .Text(LOCTEXT("QTMIpAddress", "QTM Server IP Address"))
                ]
                + SHorizontalBox::Slot()
                .HAlign(HAlign_Fill)
                .FillWidth(0.5f)
                [
                    SAssignNew(IpAddress, SEditableTextBox)
                    .Text(LOCTEXT("DefaultQTMIpAddress", "127.0.0.1"))
                    .IsEnabled(&SQTMConnectLiveLinkSourceEditor::IsAutoConnect)
                ]
            ]

            + SVerticalBox::Slot()
            .AutoHeight()
            .Padding(3.0f)
            [
                SNew(SButton)
                .Text(LOCTEXT("Create", "Create"))
                .OnClicked(this, &SQTMConnectLiveLinkSourceEditor::CreateSource)
            ]
        ]
    ];
}

FReply SQTMConnectLiveLinkSourceEditor::CreateSource() const
{
    QTMConnectLiveLinkSettings settings;
    settings.IpAddress = this->GetIpAddress();
    settings.AutoDiscover = this->GetAutoDiscover();
    OnPropertiesSelected.ExecuteIfBound(settings);
    return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE