# ESP32-Servo

## 개발 목적

Switchbot 이라는 기존 제품을 사용하면서 클라우드 서버를 통해 실행되는 프로세스로 인해 Delay가 발생하여, 추가적으로 구매하기 보단 직접 만들어서 사용하기로 함.



## 동작 프로세스

MQTT Broker를 통해 Topic을 구독하여 메시지가 발행되는지를 확인합니다.

```
// 예시
iot/switch/kitchen
```

### 예상 메시지 별 행동

| Message | Action                            |
| ------- | --------------------------------- |
| ON      | 모터의 각도를 ON으로 이동합니다.  |
| OFF     | 모터의 각도를 OFF으로 이동합니다. |
| TOGGLE  | 현 상태를 반전 시킵니다.          |



## 동작 영상

[![Video Label](http://img.youtube.com/vi/EbPd1DWbs9Y/0.jpg)](https://youtu.be/EbPd1DWbs9Y)

