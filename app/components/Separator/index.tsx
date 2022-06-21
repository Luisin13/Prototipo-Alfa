import React from "react";
import { View } from "react-native";

interface SeparatorProps {
  color?: string;
  height?: number | string;
  width?: number | string;
}

export function Separator(props: SeparatorProps & View["props"]) {
  const { color, height, width, style } = props;

  return (
    <View
      style={[
        {
          backgroundColor: color || "#4e4e4e",
          height: height || 4,
          width: width || "90%",
          borderRadius: 100,
        },
        style,
      ]}
    />
  );
}
