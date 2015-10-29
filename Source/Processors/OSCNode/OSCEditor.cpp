/*
    ------------------------------------------------------------------

    This file is part of the Open Ephys GUI
    Copyright (C) 2014 Open Ephys

    ------------------------------------------------------------------

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "OSCEditor.h"
#include "OSCNode.h"
#include "../../AccessClass.h"
#include "../../UI/EditorViewport.h"

OSCEditor::OSCEditor(GenericProcessor* parentNode, bool useDefaultParameterEditors=true)
    : GenericEditor(parentNode, useDefaultParameterEditors)

{
    desiredWidth = 180;

    adrLabel = new Label("Address", "Address:");
    adrLabel->setBounds(10,80,140,25);
    addAndMakeVisible(adrLabel);

    String defaultAddress = "/red";
    labelAdr = new Label("Address", defaultAddress);
    labelAdr->setBounds(80,85,80,18);
    labelAdr->setFont(Font("Default", 15, Font::plain));
    labelAdr->setColour(Label::textColourId, Colours::white);
    labelAdr->setColour(Label::backgroundColourId, Colours::grey);
    labelAdr->setEditable(true);
    labelAdr->addListener(this);
    addAndMakeVisible(labelAdr);
    OSCNode *p= (OSCNode *)getProcessor();
    p->setAddress(defaultAddress);

    urlLabel = new Label("Port", "Port:");
    urlLabel->setBounds(10,40,140,25);
    addAndMakeVisible(urlLabel);

    String defaultPort = "5005";
    labelPort = new Label("Port", defaultPort);
    labelPort->setBounds(80,45,80,18);
    labelPort->setFont(Font("Default", 15, Font::plain));
    labelPort->setColour(Label::textColourId, Colours::white);
    labelPort->setColour(Label::backgroundColourId, Colours::grey);
    labelPort->setEditable(true);
    labelPort->addListener(this);
    addAndMakeVisible(labelPort);
}

OSCEditor::~OSCEditor()
{
    // TODO should we delete all children, check JUCE docs
    // PS: Causes segfault if we do right now
//    deleteAllChildren();
}

void OSCEditor::labelTextChanged(Label *label)
{
    if (label == labelAdr)
    {
       Value val = label->getTextValue();

        OSCNode *p= (OSCNode *)getProcessor();
        p->setAddress(val.getValue());
    }
    if (label == labelPort)
    {
       Value val = label->getTextValue();

        OSCNode *p= (OSCNode *)getProcessor();
        p->setPort(val.getValue());
    }
}

