// Copyright (C) 2023 twyleg
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

RowLayout {
    id: advancedSlider

    property alias name: nameText.text

    property double from: 0.0
    property double to: 10.0
    property double value: 0.0
    property double stepSize: 0.1

    Text {
        id: nameText

        Layout.preferredWidth: parent.width *0.1

        clip: true

    }

    Slider {
        id: slider

        // width: parent.width * 0.6
        Layout.fillWidth: true

        from: advancedSlider.from
        to: advancedSlider.to
        value: advancedSlider.value
        stepSize: advancedSlider.stepSize

        onPositionChanged: {
            advancedSlider.value = value
        }


    }

    SpinBox {
        id: spinBox

        from: decimalToInt(advancedSlider.from)
        to: decimalToInt(advancedSlider.to)
        value: decimalToInt(advancedSlider.value)
        stepSize: decimalToInt(advancedSlider.stepSize)

        editable: true

        property int decimals: 2
        property real realValue: value / decimalFactor
        readonly property int decimalFactor: Math.pow(10, decimals)

        function decimalToInt(decimal) {
            return decimal * decimalFactor
        }

        function intToDecimal(decimal) {
            return decimal / decimalFactor
        }

        onValueChanged: {
            advancedSlider.value = intToDecimal(value)
        }

        validator: DoubleValidator {
            bottom: Math.min(spinBox.from, spinBox.to)
            top:  Math.max(spinBox.from, spinBox.to)
            decimals: spinBox.decimals
            notation: DoubleValidator.StandardNotation
        }

        textFromValue: function(value, locale) {
            return Number(value / decimalFactor).toLocaleString(locale, 'f', spinBox.decimals)
        }

        valueFromText: function(text, locale) {
            return Math.round(Number.fromLocaleString(locale, text) * decimalFactor)
        }
    }

}
