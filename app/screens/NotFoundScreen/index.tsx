import React from "react";
import { View } from "react-native";
import { BackToAuthButton } from "../../components/BackToAuthButton";
import ThemedText from "../../components/ThemedText";
import ThemedView from "../../components/ThemedView";

import { styles } from "./styles";

interface NotFoundScreenProps {
  setScreen: () => void;
}

export default function NotFoundScreen(props: NotFoundScreenProps) {
  return (
    <ThemedView style={styles.container} lightColor="#eee" darkColor="#1f1f1f">
      <BackToAuthButton setScreen={props.setScreen} />
    </ThemedView>
  );
}
