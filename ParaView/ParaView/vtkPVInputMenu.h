/*=========================================================================

  Program:   ParaView
  Module:    vtkPVInputMenu.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

Copyright (c) 2000-2001 Kitware Inc. 469 Clifton Corporate Parkway,
Clifton Park, NY, 12065, USA.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

 * Neither the name of Kitware nor the names of any contributors may be used
   to endorse or promote products derived from this software without specific 
   prior written permission.

 * Modified source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/
// .NAME vtkPVInputMenu menu for selecting input for a source.
// .SECTION Description
// This menu uses vtkPVSources as entries instead of vtkPVDatas.
// Use of the first input is hard coded.  If we want to allow more
// than one output, then this widget will have to be changed.

#ifndef __vtkPVInputMenu_h
#define __vtkPVInputMenu_h

#include "vtkPVWidget.h"

class vtkDataSet;
class vtkKWLabel;
class vtkKWOptionMenu;
class vtkPVData;
class vtkPVSourceCollection;

class VTK_EXPORT vtkPVInputMenu : public vtkPVWidget
{
public:
  static vtkPVInputMenu* New();
  vtkTypeMacro(vtkPVInputMenu, vtkPVWidget);
  void PrintSelf(ostream& os, vtkIndent indent);
  
  // Description:
  // Create the widget.
  virtual void Create(vtkKWApplication *app);

  // Description:
  // Set the label.  The label can be used to get this widget
  // from a script.
  void SetLabel (const char* label);
  const char* GetLabel();

  // Description:
  // This is the source collection as possible inputs.
  // If the collection gets modified, it will be reflected
  // in the menu on the next Reset call.
  // The collection is not referce counted for fear of loops 
  // and memory leaks.  We may wnet to fix his later.
  void SetSources(vtkPVSourceCollection *sources);
  vtkPVSourceCollection *GetSources();

  // Description:
  // Set/Get the class type for this input menu
  vtkSetStringMacro(InputType);
  vtkGetStringMacro(InputType);
  
  // Description:
  // The input name is usually "Input", but can be something else
  // (i.e. Source). Used to format commands in accept and reset methods.
  vtkSetStringMacro(InputName);
  vtkGetStringMacro(InputName);
  
  // Description:
  // Gets called when the accept button is pressed.
  // This method may add an entry to the trace file.
  virtual void Accept();

  // Description:
  // Gets called when the reset button is pressed.
  virtual void Reset();

  // Description:
  // This method gets called when the user changes the widgets value,
  // or a script changes the widgets value.  Ideally, this method should 
  // be protected.  Input menus have the specifie behaviour that
  // the widgets Accept method is called when ever the input menu is changed.
  virtual void ModifiedCallback();

  // Description:
  // Set the menus value as a string.
  // Used by the Accept and Reset callbacks.
  void SetCurrentValue(vtkPVSource *pvs);
  vtkPVSource* GetCurrentValue() { return this->CurrentValue;}
  
  // Description:
  // It is sort of weird that the value of the menu is a vtkPVSource.
  // This method returns the output of the source, 
  // so the menu can be used more naturally.
  vtkPVData* GetPVData();

  // Description:
  // Get the vtk data set of the current value.
  vtkDataSet* GetVTKData();

  // Description:
  // Menu callback when an item is selected.
  void MenuEntryCallback(vtkPVSource *pvs);

  // Description:
  // Save this widget to a file.  
  virtual void SaveInTclScript(ofstream *file);

  // Description:
  // This is the name used to set the input in the VTK filter.
  // It is needed to save tcl scripts.
  vtkSetStringMacro(VTKInputName);
  vtkGetStringMacro(VTKInputName);

//BTX
  // Description:
  // Creates and returns a copy of this widget. It will create
  // a new instance of the same type as the current object
  // using NewInstance() and then copy some necessary state 
  // parameters.
  vtkPVInputMenu* ClonePrototype(vtkPVSource* pvSource,
				 vtkArrayMap<vtkPVWidget*, vtkPVWidget*>* map);
//ETX

protected:
  vtkPVInputMenu();
  ~vtkPVInputMenu();


  char* InputType;
  char* InputName;
  char *VTKInputName;
  
  vtkPVSource *CurrentValue;
  vtkPVSourceCollection *Sources;
  
  vtkKWLabel *Label;
  vtkKWOptionMenu *Menu;

  // Description:
  // Reset the menu by taking all entries out.
  void ClearEntries();

  // Description:
  // Add an entry to the menu.
  // If the source is not the right type, then this does nothing.
  // Returns 1 if a new entry was created, 0 if not the right type.
  int AddEntry(vtkPVSource *pvs);

  // Description:
  // Adds a collection of sources to the menu.
  // The sources are filtered by "InputType".
  void AddSources(vtkPVSourceCollection *sources);

  vtkPVInputMenu(const vtkPVInputMenu&); // Not implemented
  void operator=(const vtkPVInputMenu&); // Not implemented

//BTX
  virtual void CopyProperties(vtkPVWidget* clone, vtkPVSource* pvSource,
			      vtkArrayMap<vtkPVWidget*, vtkPVWidget*>* map);
//ETX
  
  int ReadXMLAttributes(vtkPVXMLElement* element,
                        vtkPVXMLPackageParser* parser);
};

#endif
