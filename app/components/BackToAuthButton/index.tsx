import React from "react";
import ThemedText from "../ThemedText";
import ThemedTouchableOpacity from "../ThemedTouchableOpacity";
import ThemedView from "../ThemedView";

import { styles } from "./styles";

interface BackToAuthButtonProps {
  setScreen: () => void;
}

export function BackToAuthButton(props: BackToAuthButtonProps) {
  return (
    <ThemedView darkColor="#1c1c1c" style={styles.container}>
      <ThemedText style={styles.text}>Aperte o botão para</ThemedText>
      <ThemedText style={styles.text}>voltar a autenticação</ThemedText>
      <ThemedTouchableOpacity style={styles.button} onPress={props.setScreen}>
        <ThemedText style={styles.buttonText}>Voltar</ThemedText>
      </ThemedTouchableOpacity>
    </ThemedView>
  );
}
