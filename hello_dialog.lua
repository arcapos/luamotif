local motif = require 'motif'

function popup(button)
	local dialog = button:CreateInformationDialog("info")

	dialog.messageString = "Hello, world!"
	dialog.okCallback = function ()
		print('OK was pressed')
	end

	motif.Realize(button:XtParent(), dialog)

	dialog:XtParent():Popup(motif.GrabNone)
end

motif.SetLanguageProc(nil, nil, nil)

resources = {
	'*fontList: variable',
	'*renderTable: variable',
	'*renderTable.variable.fontName: Arial',
	'*renderTable.variable.fontSize: 14',
	'*renderTable.variable.fontType: FONT_IS_XFT',

	--  Color definitions

	'*foreground: #000000',
	'*background: #c1c1c1',
	'*XmList.background: #999999',
	'*XmPushButton.background: #999999',
	'*XmDrawnButton.background: #999999',
	'*XmRowColumn*OptionButton.background: #999999',
	'*XmArrowButton.background: #c1c1c1',
	'*XmText.background: #b98e8e',
	'*XmScrolledWindow.XmText.background: #000000',
	'*XmTextField.background: #b98e8e',
	'*XmScrollBar.background: #999999',
	'*XmScrollBar.foreground: #999999',
	'*XmScale*foreground: #000000',
	'*XmMenuShell*background: #c1c1c1',
	'*XmMenuShell*XmToggleButton.selectColor: #000000',
	'*highlightColor: #000000',
	'*form*statusBar*foreground: #c1c1c1',
	'*form*statusBar*troughColor: #b98e8e',
	'*form*helpButton*background: #9f8484',
	'*form*textLabel*background: #999999'
}

app, toplevel = motif.Initialize("Demos", resources)

rc = motif.RowColumn {
	motif.PushButton {
		labelString = "Hello",
		activateCallback = popup
	},
	motif.PushButton {
		labelString = "Goodbye",
		activateCallback = function () app:SetExitFlag() end
	}
}

motif.Realize(toplevel, rc)
app:MainLoop()
