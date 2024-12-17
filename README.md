# HoloCure_Imitaion

이 프로젝트는 HoloLive의 팬게임인 HoloCure를 참고해서 만든 게임입니다.
HoloCure는 일정의 뱀서라이크 게임입니다.

이미지 출처 : https://www.spriters-resource.com/search/?q=holocure

작업 중 참조 : https://holocure.fandom.com/wiki/HoloCure_Wiki

### 1. 플레이 화면

![bandicam2024-06-0520-26-59-556-ezgif com-video-to-gif-converter_(1) (1)](https://github.com/user-attachments/assets/1f8402db-ddc5-476c-a870-31552405b0b7)


### 2. 구현된 플레이어블 케릭터
- Watson

![bandicam2024-05-1616-18-28-984-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/5133edda-cc02-464b-9a84-4ba8672c6108)

- Kiara

![bandicam2024-05-1616-22-42-145-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/05786ab3-7ccc-4900-9e4a-7067d6449eb6)

- Baelz

![bandicam2024-05-1616-20-40-959-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/65f13093-c179-462d-b4ef-ba374f84c36b)


총 3 체의 플레이어블 캐릭터가 구현됨

### 3. 구현된 스킬
- 현재 5개의 Status 상승 스킬(공격력 상승, 크리티컬 확률 상승, 최대 체력 상승, 아이템 획득 범위 상승, 이동 속도 상승)이 구현
- 현재 8개의 공격 스킬(3개는 각 캐릭터의 기본 공격 스킬, 5개는 레벨업 및 강적 처치 보상으로 획득) + 1개의 구현 중인 공격 스킬이 존재
- 현재 7개의 버프 스킬(강화 횟수 증가, 회복량 증가, Exp 획득량 증가, 이동속도 상승, Coin 획득량 상승, 지속적 회복, 최대 체력 증가 + 공격력 상승)이 구현됨

### 3. 맵 구현

- 타일 이동

![bandicam2024-06-0313-38-11-475-ezgif com-video-to-gif-converter (1)](https://github.com/user-attachments/assets/aa2ace44-9991-4102-a1c6-28fee235a864)

- 반투명 처리

![bandicam2024-06-0520-26-59-556-ezgif com-video-to-gif-converter_(1) (1)](https://github.com/user-attachments/assets/bf04cf80-d330-4e5b-9c91-1bf32ba50ef4)

- BackGroundManager 클래스에서 관리
- 플레이어의 이동 방향과 타일과 플레이어의 거리에 따라 타일이 이동하도록 구현
- 타일 생성 시 타일 번호에 따라 Tree, Flower, Grass가 생성
- Tree, Flower, Grass의 활성은 정해진 확률에 따라 결정
-  각 좌표에서 Tree, Flower, Grass의 활성 여부를 기록해 두었다가 해당 좌표에 돌아오면 재활용
- Tree, Flower, Grass에서 좌표에 따른 활성 여부를 map으로 기록
- Tree에 spatial partition을 적용, 플레이어와의 충돌 및 플레이어가 나무 뒤에 가려지는 경우 반투명해지는 기믹 구현
- Flower에도 반투명해지는 기믹 적용

### 4. 충돌 처리
- 충돌 처리 최적화에 Spatial Partition(공간 분할)을 참조해보았다.
- 참조 자료 : https://gameprogrammingpatterns.com/spatial-partition.html
- Spatial Partition은 간 관리 기법으로, 큰 공간을 더 작은 구역(영역)으로 나누어 객체나 데이터를 효율적으로 관리하고 탐색하는 방법이다.
- 게임 공간을 특정한 크기를 가지는 Cell로 나누어 객체(Enemy, Player, Projectile, Item)들을 Cell마다 나누어 저장시켰다.
- 객체가 존재하는 Cell + Cell에 인접한 8개의 Cell에서 충돌 가능성 있는 노드를 찾아 충돌 처리를 시켰다. (이 부분에 대해서는 아직 더 최적화할 여지가 존재한다)
- 충돌 가능성의 여부는 '두 객체의 충돌체의 대각선 길이의 합 < 두 객체의 중심 좌표의 차' 일 경우 충돌 가능성이 있다고 판단하고 이 경우에만 충돌 검사를 실행하였다.

### 5. Text 출력
- 사용중인 DX 버전에 Text 출력을 지원하는 기능이 없어 직접 만들어보기로 했다.
- siwtch문을 사용해서 입력받은 문자에 대응하는 이미지를 출력하는 방식을 사용했다.
- 문제는 각 글자에 사용할 가능성이 있는 모든 글자 이미지를 저장했다는 점이다. 이 점은 추후 수정할 필요가 존재한다.

## 추후 작업할 내용
- BossEnemy 및 SpecialEnemy 구현
- 각 부분에서 최적화 진행
- Interface를 사용해서 공통되는 부분을 분리
- 효과음, 배경음 추가
- 시작 씬, 케릭터 선택 씬 구현
- 저장 기능 구현 
-> 캐릭터 해금 여부, 강화 정도, 보유한 코인의 양은 게임을 재시작할 때 남아있어야 할 요소.
- 무기 합체 구현 
-> 뱀서 라이크 게임의 꽃이라 생각하는 요소.
-> 서로 다른 무기가 결합해 하나의 강력한 무기가 되는 것, 숨겨져있는 조합을 찾아내는 것
