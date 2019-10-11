PULSONIX_LIBRARY_ASCII "SamacSys ECAD Model"
//358578/184125/2.44/4/4/Transistor

(asciiHeader
	(fileUnits MM)
)
(library Library_1
	(padStyleDef "c110_h70"
		(holeDiam 0.7)
		(padShape (layerNumRef 1) (padShapeType Ellipse)  (shapeWidth 1.1) (shapeHeight 1.1))
		(padShape (layerNumRef 16) (padShapeType Ellipse)  (shapeWidth 1.1) (shapeHeight 1.1))
	)
	(padStyleDef "s110_h70"
		(holeDiam 0.7)
		(padShape (layerNumRef 1) (padShapeType Rect)  (shapeWidth 1.1) (shapeHeight 1.1))
		(padShape (layerNumRef 16) (padShapeType Rect)  (shapeWidth 1.1) (shapeHeight 1.1))
	)
	(textStyleDef "Normal"
		(font
			(fontType Stroke)
			(fontFace "Helvetica")
			(fontHeight 1.27)
			(strokeWidth 0.127)
		)
	)
	(patternDef "DIP762W50P254L460H390Q4N" (originalName "DIP762W50P254L460H390Q4N")
		(multiLayer
			(pad (padNum 1) (padStyleRef c110_h70) (pt -3.81, 1.27) (rotation 90))
			(pad (padNum 2) (padStyleRef c110_h70) (pt -3.81, -1.27) (rotation 90))
			(pad (padNum 3) (padStyleRef c110_h70) (pt 3.81, -1.27) (rotation 90))
			(pad (padNum 4) (padStyleRef s110_h70) (pt 3.81, 1.27) (rotation 90))
		)
		(layerContents (layerNumRef 18)
			(attr "RefDes" "RefDes" (pt 0, 0) (textStyleRef "Normal") (isVisible True))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt -4.61 2.55) (pt 4.61 2.55) (width 0.05))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt 4.61 2.55) (pt 4.61 -2.55) (width 0.05))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt 4.61 -2.55) (pt -4.61 -2.55) (width 0.05))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt -4.61 -2.55) (pt -4.61 2.55) (width 0.05))
		)
		(layerContents (layerNumRef 28)
			(line (pt -3.25 2.3) (pt 3.25 2.3) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt 3.25 2.3) (pt 3.25 -2.3) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt 3.25 -2.3) (pt -3.25 -2.3) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt -3.25 -2.3) (pt -3.25 2.3) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt -3.25 1.03) (pt -1.98 2.3) (width 0.025))
		)
		(layerContents (layerNumRef 18)
			(line (pt -4.36 2.3) (pt 3.25 2.3) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt -3.25 -2.3) (pt 3.25 -2.3) (width 0.2))
		)
	)
	(symbolDef "K1010_B" (originalName "K1010_B")

		(pin (pinNum 1) (pt 0 mils 0 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -25 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 2) (pt 0 mils -100 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -125 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 3) (pt 1500 mils 0 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 1270 mils -25 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 4) (pt 1500 mils -100 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 1270 mils -125 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(line (pt 200 mils 100 mils) (pt 1300 mils 100 mils) (width 6 mils))
		(line (pt 1300 mils 100 mils) (pt 1300 mils -200 mils) (width 6 mils))
		(line (pt 1300 mils -200 mils) (pt 200 mils -200 mils) (width 6 mils))
		(line (pt 200 mils -200 mils) (pt 200 mils 100 mils) (width 6 mils))
		(attr "RefDes" "RefDes" (pt 1350 mils 300 mils) (justify Left) (isVisible True) (textStyleRef "Normal"))
		(attr "Type" "Type" (pt 1350 mils 200 mils) (justify Left) (isVisible True) (textStyleRef "Normal"))

	)
	(compDef "K1010_B" (originalName "K1010_B") (compHeader (numPins 4) (numParts 1) (refDesPrefix Q)
		)
		(compPin "1" (pinName "ANODE") (partNum 1) (symPinNum 1) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "2" (pinName "CATHODE") (partNum 1) (symPinNum 2) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "4" (pinName "COLLECTOR") (partNum 1) (symPinNum 3) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "3" (pinName "EMITTER") (partNum 1) (symPinNum 4) (gateEq 0) (pinEq 0) (pinType Unknown))
		(attachedSymbol (partNum 1) (altType Normal) (symbolName "K1010_B"))
		(attachedPattern (patternNum 1) (patternName "DIP762W50P254L460H390Q4N")
			(numPads 4)
			(padPinMap
				(padNum 1) (compPinRef "1")
				(padNum 2) (compPinRef "2")
				(padNum 3) (compPinRef "3")
				(padNum 4) (compPinRef "4")
			)
		)
		(attr "Manufacturer_Name" "Cosmo")
		(attr "Manufacturer_Part_Number" "K1010 B")
		(attr "Mouser Part Number" "")
		(attr "Mouser Price/Stock" "")
		(attr "RS Part Number" "3956344")
		(attr "RS Price/Stock" "http://uk.rs-online.com/web/p/products/3956344")
		(attr "Description" "Opto-isolator,K1010B 5000Vac/50mA DIP4 Cosmo K1010 B Transistor Output Optocoupler, Through Hole, 4-Pin DIP")
		(attr "<Hyperlink>" "http://www.cosmo-ic.com/object/products/k1010.pdf")
		(attr "<Component Height>" "3.9")
		(attr "<STEP Filename>" "K1010_B.stp")
		(attr "<STEP Offsets>" "X=0;Y=0;Z=0")
		(attr "<STEP Rotation>" "X=0;Y=0;Z=0")
	)

)
